const Discord = require("discord.js");
const https = require('https');
module.exports.run = async (bot, message, args) => {
    
    https.get('https://api.shaqodoon.ro/total/', (res) => {
        console.log('statusCode:', res.statusCode);
        console.log('headers:', res.headers);
  
        res.on('data', (result) => {
            var data = JSON.parse(result);
            data = data["total"];
            
            const embed = new Discord.MessageEmbed()
                .setColor('#ff8800')
                .setTitle('shaqo doon')
                .setURL('https://shaqodoon.ro/')
                .addFields(
                    { name: data["jobs"], value: 'joburi', inline: true },
                    { name: data["companies"], value: 'companii', inline: true },
                )
                .setThumbnail('https://images-ext-2.discordapp.net/external/ESTgVLRrK1_oiXX39q72ahOvzlgtysNLRt08g-QHh2o/https/shaqodoon.ro/shaqo_doon_logo.png?width=649&height=649')
            message.channel.send(embed);
        });
    }).on('error', (e) => {
        console.error(e);
    });  
}

module.exports.help = {
  name:"total"
}
