/* Modules */
const express = require('express');
const path = require('path');
const multer = require('multer');
const fs = require('fs');
const bodyParser = require('body-parser');
const session = require('express-session');

/* Port */
const port = 8756;

/* Files */
const db = require('./js_back/psql')
const { getExecOperator } = require("./js_back/exe");
const dl = require('./js_back/download');

/* Extensions */
const textType = [ 
    "", ".o", "", ".c", ".cpp", 
    ".java", ".sql", ".html", ".css"
];

/* File Types (Codes) */
const TCode = [ "", "010", "011", "101", "100", ];

const app = express();

/* Session */
const sess = {
  secret: 'secret',
  cookie: { maxAge: 60000 },
  resave: false,
  saveUninitialized: true,
  uid : 0,
  uname : '',
  passwd : ''
}

if (app.get('env') === 'production') {
  app.set('trust proxy', 1)
  sess.cookie.secure = true
}

app.use(session(sess))
app.use(express.static(path.join(__dirname, '.')));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded( { extended: true } ));

/* Setting Upload Strage */
const storage = multer.diskStorage({
  destination: function (req, file, cb) {
    cb(null, './Server/tmp/')
  },
  filename: function (req, file, cb) {
    cb(null, file.originalname)
  }
});
const upload = multer({ storage: storage })

/* Entry without Login */
app.get('/', (req, res) => {
  res.send('alert("ログインしてください。)"');
});

/* Entry Point */
app.post('/', (req, res) => {
  const uid = req.body.user_Id;
  const uname = req.body.user_Name;
  const passwd = req.body.user_Pass;
  if (req.session.views) {
    req.session.views++;
  } else {
    req.session.views = {uid : uid, uname : uname, passwd : passwd};
  }
  res.sendFile(path.join(__dirname, './file_main.html'))
});

/* Get User Info */
app.post('/userinfo', (req, res) => {
  res.status(200).json(req.session.views);
});

/* Test Page (Login) */
app.get('/test', (req, res) => res.sendFile(path.join(__dirname, './test.html')));

/* Get Command List */
app.get('/init_cmd_list', (req, res) => {
  const cmdSearcher = require('./js_back/CmdSearcher.js');
  return cmdSearcher.getCommandList(res);
});

/* Create Dounroad URL */
app.put('/download', async (req, res) => {
  const result = await dl.downLoad(req.body);
  return res.status(200).json(result);
});

/* Initialize Directory Entry */
app.put('/init', (req, res) => {
    const database = require('./js_back/psql.js');
    return database.getFiles(req.body.dir, req.body.uid, res);
});

app.put('/getfinfo', (req, res) => {
  const database = require('./js_back/psql');
  return database.getFileInfo(req.body.fname, req.body.uid, res);
});

/* Execute Command */
app.put('/exec', async (req, res) => {
  const execOperator = await getExecOperator();
  return execOperator.exec(req.body.dir, req.body.id, req.body.uid, res);
});

/* Make Directory */
app.put('/mkdir', async (req, res) => {
  console.log(req.body.name)
  const execOperator = await getExecOperator();
  return execOperator.mkdir(req.body.uid, req.body.name, res);
});

/* Delete File */
app.get('/delete', (req, res) => {
  const database = require('./psql.js');
  return database.deleteFile(req.body.name, res);
});

/* Upload to Server */
app.post('/upload', upload.single('file'), function (req, res, next) {

  /* Move Uploaded File To The Right Directory */
  fs.rename(req.file.path, req.body.dname + req.file.originalname + textType[req.body.type], (err) => {
    if (err) throw err;
    console.log('uploaded : ', req.body.dname + req.file.originalname + textType[req.body.type]);
  });

  /* Set File Name To Database */
  if (req.body.type == 1) {
    db.setFile(req.body.dname + req.file.originalname + '.o', req.body.uid, TCode[req.body.type]);
  } else {
    db.setFile(req.body.dname + req.file.originalname, req.body.uid, TCode[req.body.type]);
  }
  
 return res.status(200).json(true)
});

/* Listen Specified Port */
app.listen(port,function(){
	console.log(`Example app listening on port ${port}!`)
});
