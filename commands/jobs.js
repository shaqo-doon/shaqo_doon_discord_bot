const Discord = require("discord.js");
const https = require('https');
module.exports.run = async (bot, message, args) => {

    var ok = 0;

    https.get(`https://api.shaqodoon.ro/jobs/?company=${args[0]}`, (res) => {
        const { statusCode } = res;
        const contentType = res.headers['content-type'];

        res.setEncoding('utf8');
        let rawData = '';
        res.on('data', (chunk) => { rawData += chunk; });
        res.on('end', () => {
        try {
            var data = JSON.parse(rawData);
            data = data["jobs"];
            console.log(data);
            var lim = 0;
            if(rawData!="{\"jobs\":[]}")
            {
                const embed = new Discord.MessageEmbed()
                .setColor('#ff8800')
                .setTitle(`Vezi toate joburile de la ${args[0]}`)
                .setURL('https://shaqodoon.ro/')
                .setThumbnail('https://images-ext-2.discordapp.net/external/ESTgVLRrK1_oiXX39q72ahOvzlgtysNLRt08g-QHh2o/https/shaqodoon.ro/shaqo_doon_logo.png?width=649&height=649')
                data.forEach(job => {
                    if (lim < 10) {
                        embed.addField(`${job["title"]} - ${job["city"]} , ${job["country"]}`,job["link"]);
                    }
                    lim++;
                });
                message.channel.send(embed); 
            }else{
                ok++;
            }
            
        } catch (e) {
            console.error(e.message);
        }
    });

    }).on('error', (e) => {
        // console.error(e);
    });

    https.get(`https://api.shaqodoon.ro/jobs/?city=${args[0]}`, (res) => {
        const { statusCode } = res;
        const contentType = res.headers['content-type'];

        res.setEncoding('utf8');
        let rawData = '';
        res.on('data', (chunk) => { rawData += chunk; });
        res.on('end', () => {
        try {
            var data = JSON.parse(rawData);
            data = data["jobs"];
            console.log(data);
            var lim = 0;
            if(rawData!="{\"jobs\":[]}")
            {
                const embed = new Discord.MessageEmbed()
                .setColor('#ff8800')
                .setTitle(`Vezi toate joburile din ${args[0]}`)
                .setURL('https://shaqodoon.ro/')
                .setThumbnail('https://images-ext-2.discordapp.net/external/ESTgVLRrK1_oiXX39q72ahOvzlgtysNLRt08g-QHh2o/https/shaqodoon.ro/shaqo_doon_logo.png?width=649&height=649')
                data.forEach(job => {
                    if (lim < 10) {
                        embed.addField(`${job["title"]} - ${job["city"]} , ${job["country"]}`,job["link"]);
                    }
                    lim++;
                });
                message.channel.send(embed); 
            }else{
                ok+=10;
            }
            
        } catch (e) {
            console.error(e.message);
        }
    });

    }).on('error', (e) => {
        // console.error(e);
    });

    https.get(`https://api.shaqodoon.ro/jobs/?country=${args[0]}`, (res) => {
        const { statusCode } = res;
        const contentType = res.headers['content-type'];

        res.setEncoding('utf8');
        let rawData = '';
        res.on('data', (chunk) => { rawData += chunk; });
        res.on('end', () => {
        try {
            var data = JSON.parse(rawData);
            data = data["jobs"];
            console.log(data);
            var lim = 0;
            if(rawData!="{\"jobs\":[]}")
            {
                const embed = new Discord.MessageEmbed()
                .setColor('#ff8800')
                .setTitle(`Vezi toate joburile din ${args[0]}`)
                .setURL('https://shaqodoon.ro/')
                .setThumbnail('https://images-ext-2.discordapp.net/external/ESTgVLRrK1_oiXX39q72ahOvzlgtysNLRt08g-QHh2o/https/shaqodoon.ro/shaqo_doon_logo.png?width=649&height=649')
                data.forEach(job => {
                    if (lim < 10) {
                        embed.addField(`${job["title"]} - ${job["city"]} , ${job["country"]}`,job["link"]);
                    }
                    lim++;
                });
                message.channel.send(embed);
            }else{
                ok+=100;
            }
            
        } catch (e) {
            console.error(e.message);
        }
    });

    }).on('error', (e) => {
        // console.error(e);
    });

    setTimeout(() => {
        console.log(ok);
        if(ok == 111)
        {
            message.channel.send(`nu exista joburi in ${args[0]}, sau serverul nu a raspuns destul de repede`);
        }
        return;
    }, 1000);
    
}

module.exports.help = {
    name: "jobs"
}
