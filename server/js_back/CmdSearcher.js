const { getPostgresClient } = require("./loginDB");

class CmdSearcher {
    async getCommandList(res) {
        const client = await getPostgresClient();
        let result = await client.execute(
                         "SELECT CNAME FROM CMDTABLE ORDER BY CCODE ASC;"
                     );
        client.release();
        let cnames = [];
        for (let i = 0; i < result.length; ++i) {
            cnames.push(result[i].cname);
        }
        return res.status(200).json(cnames);
    };
}

module.exports = new CmdSearcher()