const { EventEmitter } = require('events');

class Ticker extends EventEmitter {
  constructor(tickTime = 50) {
    super();
    this.tickTime = tickTime;
    this.tickNumber = 0;
    this.duration = 0;
  }

  tick(time, cb) {
    this.tickNumber = 0;
    this.duration = time;

    // 시작하자마자 동기 함수 __emitTick 호출을 위한 비동기화
    setImmediate(() => {
      this.__emitTick();
      this.__recursive(cb);
    })

    return this;
  }

  __emitTick() {
    if (Date.now() % 5 === 0) {
      this.emit('error', new Error('Timestamp Error'));
    }
    this.emit('tick', this.tickNumber);
    this.tickNumber++;
    this.duration -= this.tickTime;
  }

  __recursive(cb) {
    if (this.duration <= 0) {
      return cb(null, this.tickNumber);
    }
    setTimeout(() => {
      this.__emitTick();

      this.__recursive(cb);
    }, this.tickTime);
  }
}

const ticker = new Ticker(50);

ticker.tick(200, (err, data) => console.log(`The number of ticks : ${data}`))
  .on('tick', (number) => console.log(`${number} : TICK!`))
  .on('error', (err) => console.log(`Error: ${err.message}`));