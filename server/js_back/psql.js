const { getPostgresClient } = require("./loginDB");

class Database {
    constructor() {
    };

    async chNameFromSymToDir(name) {
        let sym = { code: 0 };
        let dir = { code: 0 ,
                    name: "" 
                  };

        sym.code = await this.getSymCode(name);
        dir.code = await this.getParCode(sym.code);
        dir.name = await this.getDirName(dir.code);

        return dir.name;
    };

    async getFiles(dir, uid, res) {
        let entries;
        let files = new Array();

        if (dir.type === 'SYM') {
            dir.name = await this.chNameFromSymToDir(dir.name);
            dir.type = 'DIR';
        };

        entries = await this.getEntry(dir.name);
        let i = 0;
        while (i < entries.length) {
			let infos = [];
			/* getFileInfo と共通 */
            let attr;
            const type = entries[i].attr.slice(0, 3);
            const owner_attr = entries[i].attr.slice(3, 7);
            const other_attr = entries[i].attr.slice(7);

            if ((entries[i].oid == uid) || uid >= 90000000) {
                attr = type + owner_attr;
            } else {
                attr = type + other_attr;
            }
            
            let ccodes = [];
            ccodes = await this.getInfo(attr);
            for (let i = 0; i < ccodes.length; i++) {
                let ret = await this.chFromCcodeToCname(ccodes[i].command);
                infos.push(ret[0].cmds);
            }
            const ftype = await this.getType(type);
            files.push({
                name: entries[i].name,
                cmds: infos,
                type: ftype[0].tname
            });
            i++;
        };
        return res.status(200).json(files);
    };


    async deleteFile(file, res) {
        const client = await getPostgresClient();
        if (file.type === 'DIR') {
            file.name = file.name + '/% AND FNAME = ' + file.name;
        } else if (file.type === 'SYM') {
            await client.execute(
            "DELETE FROM SYMLINKS WHERE SNAME = $1"
            );
        };
        await client.execute(
            "DELETE FROM FILES WHERE FNAME = $1"
            , [file.name]
        )
        client.release();
        return res.status(200).send(file.name + " を削除しました");
    };

    async createDir(uid, name) {
        
        const client = await getPostgresClient();
        await client.execute(
            "INSERT INTO FILES(FNAME, OID, ATTR) VALUES($1, $2, B'00111111111');"
            , [name, uid]
        ); 
        await client.release();
        
        return true;    // 成功
    };

    async getSymCode(name) {
        const client = await getPostgresClient();
        const symcode = await client.execute(
                              "SELECT FCODE FROM FILES WHERE FNAME = $1",
                              [name]
                        );
        client.release();
        return symcode[0].fcode;
    };

    async getParCode(sym_code) {
        const client = await getPostgresClient();
        const parCode = await client.execute(
                              "SELECT FCODE FROM SYMLINKS WHERE SCODE = $1",
                              [sym_code]
                        );
        client.release();
        return parCode[0].fcode;
    };

    async getDirName(dcode) {
        const client = await getPostgresClient();
        const dname = await client.execute(
                            "SELECT FNAME FROM FILES WHERE FCODE = $1",
                            [dcode]
                      );
        client.release();
        return dname[0].fname;
    };

    async getEntry(dname) {
        const client = await getPostgresClient();
        const entry = await client.execute(
                            "SELECT FNAME AS name, OID AS oid, ATTR AS attr, (ATTR & B'11100000000') AS types FROM FILES WHERE FNAME LIKE $1 || '/%' AND FNAME NOT LIKE $1 || '/%/%';", [dname]
                      );
        client.release();
        return entry;
    };

    async getInfo(attr) {
        const client = await getPostgresClient();
        const info = await client.execute(
                           "SELECT CCODE AS command FROM EXECUTABLES WHERE (ATTR_CODE::int >> 4) = (B'" + attr + "'::int >> 4) AND (((ATTR_CODE & B'0001111') & (B'" + attr + "' & B'0001111'))::int > 0);"
                     );
        client.release();
        return info;
    };


    
    async chFromCcodeToCname(code) {
        const client = await getPostgresClient();
        const name = await client.execute(
                           "SELECT CNAME AS cmds FROM CMDTABLE WHERE CCODE = $1;", [code]
                     );
        client.release();
        return name;
    } 

    async getType(ftype) {
        const client = await getPostgresClient();
        const type = await client.execute(
                           "SELECT TNAME FROM FILE_TYPES WHERE TCODE = B'" + ftype + "00000000';"
                     );
        client.release();
        return type;
    }

	/* まだ init.js に追加していない */
	async getFileInfo(fname) {
		let file;
		const client = await getPostgresClient();
        const info = await client.execute(
						"SELECT FNAME AS name, OID AS oid, ATTR AS attr FROM FILES WHERE FNAME = $1;",
						[fname]
					 );
		client.release();
		
		let attr;
        const type = info.attr.slice(0, 3);
        const owner_attr = info.attr.slice(3, 7);
        const other_attr = info.attr.slice(7);
		
		if (info.oid == uid) {
            attr = type + owner_attr;
        } else {
            attr = type + other_attr;
        }
         
        let infos = await this.getInfo(attr);
        let ftype = await this.getType(type);

		file = {
			name: entries[i].name,
            cmds: infos,
            type: ftype
        };
		return file;
	}

    async getTCode(name) {
        const client = await getPostgresClient();
        const tcode = await client.execute(
                           "SELECT TCODE FROM FILE_TYPES WHERE TNAME = $1;", [name]
                     );
        client.release();
        return tcode[0].tcode;
    }

    async getCattr(id) {
        const client = await getPostgresClient();
        const cattr = await client.execute(
                           "SELECT CATTR FROM CMDTABLE WHERE CCODE = $1;", [id]
                     );
        client.release();
        return cattr[0].cattr;
    }

    async searchExecCode (id, type) {
        var tcode = await this.getTCode(type);
        const cattr = await this.getCattr(id);
        tcode = tcode.slice(0, 3);
        const attr_code = 'B' + tcode + cattr + '';
        const client = await getPostgresClient();
        const ecode = await client.execute(
						"SELECT ECODE FROM EXECUTABLES WHERE CCODE = $1 AND ATTR_CODE = $2;",
						[id, attr_code]
					 );
		client.release();
        return ecode;
    }

    async setFile(fname, oid, type) {
        const client = await getPostgresClient();
        if (fname.includes('教材')) {
            await client.execute(
                "INSERT INTO FILES(FNAME, OID, ATTR) VALUES ($1, $2, B'" + type + "11111010');", 
                [fname, oid]
          );
        } else {
            await client.execute(
                            "INSERT INTO FILES(FNAME, OID, ATTR) VALUES ($1, $2, B'" + type + "11110000');", 
                            [fname, oid]
                        );
        }
        client.release();
    }
};

const db = new Database();
module.exports = db;
