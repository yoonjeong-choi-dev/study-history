// compose 함수 직접 구현
const compose = (...fns) => (arg) => 
    fns.reduce((composed, f) => f(composed), arg);

// 콘솔 관리 및 시간 함수
const secToMilli = () => 1000;
const getCurrentTime = () => new Date();
const clear = () => console.clear();
const log = message => console.log(message);

// 데이터 변환 함수 : 불편 함수 => 원본 객체를 복사하여 변환 후 새로운 객체 반환
const serializeClockTime = date => ({
    hours: date.getHours(),
    minutes: date.getMinutes(),
    seconds: date.getSeconds()
});

const civilianHours = clockTime => ({
    ...clockTime,
    hours: clockTime.hours > 12 ? clockTime.hours-12 : clockTime.hours
});

const appendAMorPM = clockTime => ({
    ...clockTime,
    ampm: clockTime.hours >= 12 ? "PM" : "AM"
});

// 고차 함수
const display = iowriter => (time => iowriter(time));

const formatClock = format => (time => 
    format.replace("hh", time.hours)
        .replace("mm", time.minutes)
        .replace("ss", time.seconds)
        .replace("tt", time.ampm)
);

const penddingZero = key => (clockTime => ({
    ...clockTime,
    [key]: (clockTime[key] < 10)? "0" + clockTime[key] : clockTime[key]
}));


// 주기능 함수 합성
const convertToCivilianTime = clockTime => compose(
    appendAMorPM,
    civilianHours
)(clockTime);

const doubleDigits = civilianTime => compose(
    penddingZero("hours"),
    penddingZero("minutes"),
    penddingZero("seconds")
)(civilianTime);

const startTicking = () => setInterval(compose(
    clear,
    getCurrentTime,
    serializeClockTime,
    convertToCivilianTime,
    doubleDigits,
    formatClock("hh:mm:ss tt"),
    display(log)
), secToMilli());

startTicking();