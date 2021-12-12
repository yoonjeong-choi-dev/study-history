const Sequelize = require('sequelize');

module.exports = class Domain extends Sequelize.Model {
    static init(sequelize) {
        return super.init({
            host: {
                type: Sequelize.STRING(80),
                allowNull: false
            },
            type: {
                type: Sequelize.ENUM('free', 'premium'),
                allowNull: false
            },
            // API 서버를 이용할 수 있는 인증된 백엔드 클라이언트에게 발급하는 비밀키
            clientSecret: {
                type: Sequelize.UUID,
                allowNull: false
            },
            // API 서버를 이용할 수 있는 인증된 프론트엔드 클라이언트에게 발급하는 비밀키
            frontSecret: {
                type: Sequelize.UUID,
                allowNull: false
            },
        }, {
            sequelize,
            timestamps: true,
            underscored: false, // 테이블 필드 이름을 스네이크 케이스로
            modelName: 'Domain',
            tableName: 'domains',
            paranoid: true,     // 생성, 수정, 삭제 시간 필드 추가
        });
    }

    static associate(db) {
        // 사용자 : 도메인 = 1 : N
        // 1명의 클라이언트가 여러 개의 도메인 등록 가능
        db.Domain.belongsTo(db.User);
    }
}