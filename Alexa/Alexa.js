const Alexa = require('ask-sdk-core');
const http = require('http');

function getTemp() {
    return new Promise(((resolve, reject) => {
        var options = {
            host: '193.168.146.113',
            port: 80,
            path: '/esp/get.php',
            method: 'GET',
        };

        const request = http.request(options, (response) => {
            response.setEncoding('utf8');
            let returnData = '';
            console.log(response);

            response.on('data', (chunk) => {
                returnData += chunk;
            });

            response.on('end', () => {
                resolve(returnData);
            });

            response.on('error', (error) => {
                reject(error);
            });
        });
        request.end();
    }));
}


const tempHandler = {
    canHandle(handlerInput) {
        return Alexa.getRequestType(handlerInput.requestEnvelope) === 'LaunchRequest';
    },
    async handle(handlerInput) {

        const rep = await getTemp();

        return handlerInput.responseBuilder.speak(rep).getResponse();
    }
};


exports.handler = Alexa.SkillBuilders.custom().addRequestHandlers(tempHandler).lambda();