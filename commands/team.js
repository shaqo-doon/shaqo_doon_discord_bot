
const Discord = require("discord.js");
const https = require('https');
module.exports.run = async (bot, message, args) => {
    
    const embed = new Discord.MessageEmbed()
    .setColor('#ff8800')
    .setTitle(`Apasa aici`)
    .setThumbnail('https://images-ext-2.discordapp.net/external/ESTgVLRrK1_oiXX39q72ahOvzlgtysNLRt08g-QHh2o/https/shaqodoon.ro/shaqo_doon_logo.png?width=649&height=649')
    .setDescription("pentru a afla mai\nmulte despre noi")
    .setURL("https://info.shaqodoon.ro");
    message.channel.send(embed);
}

module.exports.help = {
  name:"team"
}
