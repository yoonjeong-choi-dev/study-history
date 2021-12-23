const Sequelize = require('sequelize');
const schedule = require('node-schedule');

const { Good, Auction, User } = require('./models');

const refreshAuction = (good) => {
    const func = async () => {
        // 최고가 입찰 정보
        const success = await Auction.findOne({
            where: { GoodId : good.id },
            order: [['bid', 'DESC']],
            limit: 1,
        });

        // 입찰한 사람이 없는 경우 => 해당 상품 삭제
        if (!success) {
            await Good.destroy({
                where : {id: good.id}
            });
            return;
        }

        // 상품 입찰 정보 업데이트
        await Good.update({
            SoldId: success.UserId
        }, {
            where: { id: good.id }
        });

        // 입찰한 유저의 잔고 업데이트
        await User.update({
            money: Sequelize.literal(`money - ${success.bid}`)
        },{
            where: { id: success.UserId },
        });
    };

    return func;
};

exports.refreshAuction = refreshAuction;

exports.checkAuction = async () => {
    try {
        // 낙찰되지 않은 모든 상품 가져오기
        const targets = await Good.findAll({
            where: {
                SoldId: null,
            }
        });

        targets.forEach(async (good) => {
            // 경매 마감 시간 계산
            const end = new Date(good.createdAt); 
            end.setHours(end.getHours() + parseInt(good.duration));

            // 마감 이전인 경우 스케줄러 생성
            const curTime = new Date();
            if (curTime < end)  {
                schedule.scheduleJob(end, refreshAuction(good));
            }

            refreshAuction(good);
        });
    } catch(err) {
        console.log(err);
    }
};