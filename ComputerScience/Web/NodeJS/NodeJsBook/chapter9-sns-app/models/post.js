const Sequelize = require('sequelize');

module.exports = class Post extends Sequelize.Model {
    static init(sequelize) {
        return super.init({
            // 트위터는 최대 140자까지 게시 가능
            content: {
                type: Sequelize.STRING(140),
                allowNull: false,
            },
            // 이미지는 저장된 파일스토리지의 경로를 저장
            img: {
                type: Sequelize.STRING(200),
                allowNull: true,
            }
        }, {
            sequelize,
            timestamps: true,
            underscored: false, // 테이블 필드 이름을 스네이크 케이스로
            modelName: 'Post',
            tableName: 'Posts',
            paranoid: true,     // 생성, 수정, 삭제 시간 필드 추가
            // 이모티콘 저장을 위한 포멧
            charset: 'utf8mb4',    
            collate: 'utf8mb4_general_ci',
        })
    }

    static associate(db) {
        // 사용자 : 포스트 = 1 : N
        db.Post.belongsTo(db.User);

        // 포스트 : 해시태그 = N : M
        db.Post.belongsToMany(db.Hashtag, {
            through: 'PostHashtag'
        });

        // 좋아요 기능에서는 사용자 : 포스트 = N : M
        db.Post.belongsToMany(db.User, {
            through: 'UserLikesPost'
        });
    }
}