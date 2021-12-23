const Sequelize = require('sequelize');

module.exports = class Good extends Sequelize.Model {
    static init(sequelize) {
        return super.init({
            name: {
                type: Sequelize.STRING(20),
                allowNull: false,
            },
            img: {
                type: Sequelize.STRING(200),
                allowNull: true,
            },
            description: {
                type: Sequelize.STRING(200),
                allowNull: true,
            },
            price: {
                type: Sequelize.INTEGER,
                allowNull: false,
                defaultValue: 0
            },
            duration: {
                type: Sequelize.INTEGER,
                allowNull: false,
                defaultValue: 24
            }
        }, {
            sequelize,
            timestamps: true,
            paranoid: true,
            modelName: 'Good',
            tableName: 'goods',
            charset: 'utf8',
            collate: 'utf8_general_ci',
        });
    }

    static associate(db) {
        // 사용자 : 상품 <-> 1:N (한 사람이 여러 상품 등록)
        // => OwnerId를 통해 등록한 상품 접근
        db.Good.belongsTo(db.User, { as: 'Owner' });

        // 사용자 : 상품 <-> 1:N (한 사람이 여러 상품 구매)
        // => SoldId를 통해 입찰된 상품 접근 가능
        db.Good.belongsTo(db.User, { as: 'Sold' });

        // 상품 : 경매 <-> 1:N (한 상품에 대해 여러 입찰 신청)
        db.Good.hasMany(db.Auction);
    }
};