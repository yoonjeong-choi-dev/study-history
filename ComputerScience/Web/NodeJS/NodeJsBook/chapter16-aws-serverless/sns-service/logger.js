const { createLogger, format,  transports } = require('winston');

const logger = createLogger({
    // 로깅할 로그의 심각도
    level: 'info',
    // 저장할 로그 형식 : json
    format: format.json(),
    // 로그 저장 방식 : 파일로 저장
    transports: [
        new transports.File({filename: 'combined.log'}),
        new transports.File({filename: 'error.log', level: 'error'}),
    ],
});

if (process.env.NODE_ENV !== 'production') {
    logger.add(new transports.Console({format: format.simple()}));
}

module.exports = logger;