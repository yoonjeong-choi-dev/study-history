const Sequelize = require('sequelize');

module.exports = class Auction extends Sequelize.Model {
    static init(sequelize) {
        return super.init({
            // 입찰가
            bid: {
                type: Sequelize.INTEGER,
                allowNull: false,
                defaultValue: 0,
            },
            message: {
                type: Sequelize.STRING(100),
                allowNull: true,
            },
        }, {
            sequelize,
            timestamps: true,
            paranoid: true,
            modelName: 'Auction',
            tableName: 'auctions',
            charset: 'utf8',
            collate: 'utf8_general_ci',
        });
    }

    static associate(db) {
        // 사용자 : 경매 <-> 1:N (한 사람이 여러 상품에 여러 번 입찰)
        db.Auction.belongsTo(db.User);

        // 상품 : 경매 <-> 1:N (한 상품에 대해 여러 입찰 신청)
        db.Auction.belongsTo(db.Good);
    }
};