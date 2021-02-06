const Discord = require("discord.js");

module.exports.run = async (bot, message, args) => {
    var helpText = "\
    1. +total           -       totalul de joburi\n\
    2. +companies       -       arata companiile (10 companii)\n\
    3. +jobs [companie] -       arata joburile companiei (10 joburi)\n\
    4. +help            -       lista comenzilor\n\
    5. +team            -       vezi echipa noastra\n\
    "

    const embed = new Discord.MessageEmbed()
    .setColor('#ff8800')
    .setTitle(`Ajutor`)
    .setThumbnail('https://images-ext-2.discordapp.net/external/ESTgVLRrK1_oiXX39q72ahOvzlgtysNLRt08g-QHh2o/https/shaqodoon.ro/shaqo_doon_logo.png?width=649&height=649')
    .setDescription(helpText);
    message.channel.send(embed);
}

module.exports.help = {
  name:"help"
}
