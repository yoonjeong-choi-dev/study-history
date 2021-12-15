const Sequelize = require('sequelize');

module.exports = class User extends Sequelize.Model {
    static init(sequelize) {
        return super.init({
            // 이메일이 고유키로 작용
            email : {
                type: Sequelize.STRING(40),
                allowNull: true,
                unique: true
            },
            // 외부 인증인 경우 유저의 아이디/비밀번호가 null 일 수 있음
            nick: {
                type: Sequelize.STRING(15),
                allowNull: false,
            },
            password: {
                type: Sequelize.STRING(100),
                allowNull: true,
            },
            // 인증 제공자 : 로컬 or 외부 서비스(카카오)
            provider: {
                type: Sequelize.STRING(10),
                allowNull: false,
                defaultValue: 'local',
            },
            snsId: {
                type: Sequelize.STRING(30),
                allowNull: true,
            }
        }, {
            sequelize,
            timestamps: true,
            underscored: false, // 테이블 필드 이름을 스네이크 케이스로
            modelName: 'User',
            tableName: 'users',
            paranoid: true,     // 생성, 수정, 삭제 시간 필드 추가
            charset: 'utf8',
            collate: 'utf8_general_ci',
        })
    }

    static associate(db) {
        // 사용자 : 포스트 = 1 : N
        db.User.hasMany(db.Post);

        // 사용자 팔로잉은 N : M 관계
        // 동일 테이블 내 관계이기 때문에 as 옵션 필수
        // through 테이블에서 foreignKey 외래키를 이용하여 

        // 팔로워 찾기 : Followers를 찾기 위해, 해당 유저 id와 일치하는 followingId을 찾아내야함
        // => 해당 로우의 followerId가 해당 유저'를' 팔로잉 하는 유저
        db.User.belongsToMany(db.User, {
            foreignKey: 'followingId',
            as: 'Followers',  
            through: 'Follow',  // 매핑 테이블 모델 (followerId, followingId)
        });

        // 팔로잉 찾기 : Followings를 찾기 위해, 해당 유저 id와 일치하는 followerId 찾아내야함
        // => 해당 로우의 followingId가 해당 유저'가' 팔로잉 하는 유저
        db.User.belongsToMany(db.User, {
            foreignKey: 'followerId',
            as: 'Followings',
            through: 'Follow',  // 매핑 테이블 모델 (followerId, followingId)
        });

        // 좋아요 기능에서는 사용자 : 포스트 = N : M
        db.User.belongsToMany(db.Post, {
            through: 'UserLikesPost'
        });
    }
}