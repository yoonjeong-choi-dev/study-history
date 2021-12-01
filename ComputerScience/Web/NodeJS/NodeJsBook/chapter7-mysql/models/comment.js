const Sequelize = require('sequelize');

// DB 테이블에 맞게 정의
module.exports = class Comment extends Sequelize.Model {
    static init(sequelize) {
        return super.init(
            {
                comment: {
                    type: Sequelize.STRING(100),
                    allowNull: false,
                },
                created_at: {
                    type: Sequelize.DATE,
                    allowNull: false,
                    defaultValue: Sequelize.NOW
                }
            },
            {
                sequelize,
                timestamps: false,
                underscored: false,
                modelName: 'Comment',
                tableName: 'comments',
                paranoid: false,
                charset: 'utf8',
                collate: 'utf8_general_ci'
            }
        );
    }
    static associate(db) { 
        // user 테이블과의 관계 정의 => 이를 통해 JOIN 기능 자동 구현
        db.User.hasMany(db.Comment, {
            foreignKey: 'commenter',
            sourceKey: 'id'
        });
    }
};