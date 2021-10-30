const { ApolloServer } = require('apollo-server');
const { GraphQLScalarType } = require('graphql');


// graphql schema
const typeDefs = `
    # Define custom scalar type
    scalar DateTime

    # Define Photo types
    enum PhotoCategory {
        SELFIE
        PORTRAIT
        ACTION
        LANDSCAPE
        GRAPHIC
    }    

    # Define Photo 
    type Photo {
        id: ID!
        url: String!
        name: String!
        description: String
        category: PhotoCategory!
        postedBy: User!
        taggedUsers: [User!]!
        created: DateTime!
    }

    # Define User
    type User {
        githubLogin: ID!
        name: String
        avatar: String
        postedPhotos: [Photo!]!
        inPhotos: [Photo!]!
    }

    input PostPhotoInput {
        name: String!
        category: PhotoCategory=PORTRAIT
        description: String
    }

    type Query {
        totalPhotos: Int!
        allPhotos: [Photo!]!
    }

    type Mutation {
        postPhoto(input: PostPhotoInput!): Photo!
    }
`;

// graphql resolver 
// some variables for data local db
var users = [
    {
        githubLogin: "user1",
        name: "name1",
    },
    {
        githubLogin: "user2",
        name: "name2",
    },
    {
        githubLogin: "user3",
        name: "name3",
    },
    {
        githubLogin: "postPhoto-user",
        name: "postPhoto-user name",
    },
]

var photos = [
    {
        id: "1",
        name: "Photo1",
        description: "Desc 1",
        category: "ACTION",
        githubUser: "user2",
        created: "10-31-2021"
    },
    {
        id: "2",
        name: "Photo2",
        description: "Desc 2",
        category: "SELFIE",
        githubUser: "user3",
        created: "11-01-2021"
    },
    {
        id: "3",
        name: "Photo3",
        description: "Desc 3",
        category: "LANDSCAPE",
        githubUser: "user3",
        created: "7-31-2020"
    }
];

var tags = [
    { photoID: "1", userID: "user2" },
    { photoID: "2", userID: "user1" },
    { photoID: "2", userID: "user3" },
    { photoID: "3", userID: "user1" },
]

var _id = photos.length + 1;

const resolvers = {
    Query: {
        totalPhotos: () => photos.length,
        allPhotos: () => photos
    },

    Mutation: {
        postPhoto(parent, args) {
            var newPhoto = {
                id: _id++,
                ...args.input,
                created: new Date(),
                githubUser: "postPhoto-user"
            };

            
            photos.push(newPhoto);
            return newPhoto;
        }
    },

    Photo: {
        url: parent => `http://yoursite.com/img/${parent.id}.jpg`,
        postedBy: parent => {
            return users.find((user) => user.githubLogin == parent.githubUser);
        },
        taggedUsers: parent => {
            return tags.filter(tag => tag.photoID == parent.id)
                .map(tag => tag.userID)
                .map(userID => users.find((user) => user.githubLogin == userID))
        }
    },

    User: {
        postedPhotos: parent => {
            return photos.filter((photo) => photo.githubUser == parent.githubLogin)
        },
        inPhotos: parent => {
            return tags.filter(tag => tag.userID == parent.id)
                .map(tag => tag.photoID)
                .map(photoID => photos.find((photo) => photo.id == photoID))
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
};

// Define Server Instance with schema and resolver
const server = new ApolloServer({
    typeDefs,
    resolvers
})

// Run the server
server.listen()
    .then(({ url }) => console.log(`GraphQL Server is running on ${url}`));