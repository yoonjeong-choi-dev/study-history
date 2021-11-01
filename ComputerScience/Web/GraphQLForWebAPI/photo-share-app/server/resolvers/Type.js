const { GraphQLScalarType } = require("graphql");
const { ObjectID } = require("mongodb");

module.exports = {
    Photo: {
        // 직전에 생성된 사진의 경우, id 필드가 없고, _id필드만 존재
        id: parent => parent.id || parent._id,

        url: parent => `/img/photos/${parent._id}.jpg`,

        postedBy: (parent, args, { db }) => {
            return db.collection("users")
                        .findOne({ githubLogin: parent.userID });
        },

        taggedUsers: async (parent, args, { db }) => {
            const tags = await db.collection("tags").find().toArray();
            const userTagged = tags.filter(tag => tag.photoID === parent._id.toString())
                                .map(tag => tag.githubLogin);

            return db.collection("users")
                .find({ githubLogin: { $in : userTagged }})
                .toArray();
        }
    },

    User: {
        postedPhotos: (parent, args, { db }) => {
            return db.collection("photos")
                        .find({ userID: parent.githubLogin})
                        .toArray();
        },

        inPhotos: async (parent, args, { db }) => {
            const tags = await db.collection("tags").find().toArray();
            const photoIds = tags.filter(tag=> parent.githubLogin === tag.githubLogin)
                                    .map(tag => ObjectID(tag.photoID));

            return db.collection("photos")
                    .find({ _id : { $in : photosIds }})
                    .toArray();
        }
    },

    // Define custom scalar
    DateTime: new GraphQLScalarType({
        name: "DateTime",
        description: "A valid date time value",
        parseValue: value => new Date(value),
        serialize: value => new Date(value).toISOString(),
        parseLiteral: ast => ast.value
    })
}