const Sequelize = require('sequelize');

// DB 테이블에 맞게 정의
module.exports = class User extends Sequelize.Model {
    static init(sequelize) {
        return super.init(
            {
                name: {
                    type: Sequelize.STRING(20),
                    allowNull: false,
                    unique: true
                },
                age: {
                    type: Sequelize.INTEGER.UNSIGNED,
                    allowNull: false,
                },
                married: {
                    type: Sequelize.BOOLEAN,
                    allowNull: false,
                },
                comment: {
                    type: Sequelize.TEXT,
                    allowNull: true,
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
                modelName: 'User',
                tableName: 'users',
                paranoid: false,
                charset: 'utf8',
                collate: 'utf8_general_ci'
            }
        );
    }
    static associate(db) { 
        // comment 테이블과의 관계 정의
        db.Comment.belongsTo(db.User, {
            foreignKey: 'commenter',
            targetKey: 'id'
        });
    }
};