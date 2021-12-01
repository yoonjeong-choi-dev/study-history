const Sequelize = require('sequelize');

module.exports = class Hashtag extends Sequelize.Model {
    static init(sequelize) {
        return super.init({
            title: {
                type: Sequelize.STRING(15),
                allowNull: false,
                unique: true,
            }
        }, {
            sequelize,
            timestamps: true,
            underscored: false, // 테이블 필드 이름을 스네이크 케이스로
            modelName: 'Hashtag',
            tableName: 'hashtags',
            paranoid: false,     
            // 이모티콘 저장을 위한 포멧
            charset: 'utf8mb4',    
            collate: 'utf8mb4_general_ci',
        })
    }

    static associate(db) {
        // 포스트 : 해시태그 = N : M
        db.Hashtag.belongsToMany(db.Post, {
            through: 'PostHashtag'
        });
    }
}