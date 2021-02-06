const Discord = require("discord.js");
const https = require('https');
module.exports.run = async (bot, message, args) => {

    https.get('https://api.shaqodoon.ro/companies/', (res) => {
        const { statusCode } = res;
        const contentType = res.headers['content-type'];



        res.setEncoding('utf8');
        let rawData = '';
        res.on('data', (chunk) => { rawData += chunk; });
        res.on('end', () => {
            try {
                var data = JSON.parse(rawData);
                data = data["companies"];
                console.log(data);
                var lim = 0;
                
                const embed = new Discord.MessageEmbed()
                    .setColor('#ff8800')
                    .setTitle('Primele zece companii')
                    .setURL('https://shaqodoon.ro/')
                    .setThumbnail('https://images-ext-2.discordapp.net/external/ESTgVLRrK1_oiXX39q72ahOvzlgtysNLRt08g-QHh2o/https/shaqodoon.ro/shaqo_doon_logo.png?width=649&height=649')
                    data.forEach(comp => {
                        if (lim < 10) {
                            embed.addField(comp["company"], comp["link"]);
                        }
                        lim++;
                    });
                message.channel.send(embed);
            } catch (e) {
                console.error(e.message);
            }
        });
        

    }).on('error', (e) => {
        // console.error(e);
    });
}

module.exports.help = {
    name: "companies"
}
