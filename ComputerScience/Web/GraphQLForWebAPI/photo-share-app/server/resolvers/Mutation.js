const { authorizeWithGithub } = require("../utils");
const fetch = require("node-fetch")
const { ObjectID, Db } = require("mongodb");


module.exports = {
    postPhoto: async (parent, args, { db, currentUser }) => {
        // check the user is login via currentUser
        if (!currentUser) {
            throw new Error("Only an authorized user can post a photo");
        }

        var newPhoto = {
            ...args.input,
            userID: currentUser.githubLogin,
            created: new Date()
        };
    
        const { insertedIds } = await db.collection("photos").insertOne(newPhoto);
        newPhoto.id = insertedIds;
        
        return newPhoto;
    },

    githubAuth: async (parent, { code }, { db }) => {
        // Get user data from Github
        let {
            message,
            access_token,
            avatar_url,
            login,
            name
        } = await authorizeWithGithub({
            client_id: process.env.CLIENT_ID,
            client_secret: process.env.CLIENT_SECRET,
            code
        });

        // message : error
        if (message) {
            throw new Error(message);
        }

        let userInfo = {
            name,
            githubLogin: login,
            githubToken: access_token,
            avatar: avatar_url,
            type: "REAL"
        };

        // Update DB
        const updateResult
            = await db.collection("users")
                        .findOneAndReplace({ githubLogin: login }, userInfo, { upsert: true });
        
        // created
        if (!updateResult["value"]) {
            const _id = updateResult["lastErrorObject"]["upserted"];
            const user = await db.collection('users').findOne({ "_id": _id });
        }
        const user = updateResult["value"];
        
        return {user: user, token: access_token};
    },

    addFakeUsers: async (parent, { count }, { db }) => {
        // 랜덤 유저 생성 API
        let randomUserAPI = `https://randomuser.me/api/?results=${count}`;
        let { results } = await fetch(randomUserAPI).then(res => res.json());

        let users = results.map(user => ({
            githubLogin: user.login.username,
            name: `${user.name.first} ${user.name.last}`,
            avatar: user.picture.thumbnail,
            githubToken: user.login.sha1,
            type: "FAKE"
        }))

        // 유저 DB 등록
        await db.collection("users").insert(users);

        return users;
    },

    fakeUserAuth: async (parent, { githubLogin }, { db }) => {
        let user = await db.collection("users").findOne({githubLogin});

        if (!user) {
            throw Error(`Cannot find user with githubLogin "${githubLogin}""`);
        }

        return {
            token: user.githubToken,
            user
        }
    },

    deleteAllFakeUsers: async (parent, args, { db }) => {
        const fakeQuery = { "type": "FAKE"};
        const users = await db.collection("users").find(fakeQuery).toArray();
        
        const githubLogins = users.map( user => user.githubLogin );

        // 태그 기능은 없으므로, fake 사용자 및 해당 사용자가 포스트한 사진들만 삭제
        const deleteUsers = await db.collection("users").deleteMany(fakeQuery);
        const deletePhotos = await db.collection("photos").deleteMany({
            "userID": { $in: githubLogins }
        })
        
        return `${deleteUsers.deletedCount} fake-users are deleted and ${deletePhotos.deletedCount} photos are deleted`
    }
}