module.exports = {
    // 각 이벤트를 asyncIterator를 이용하여 구독
    newPhoto: {
        subscribe: (parent, args, {pubsub}) => {
            console.log("addPhoto : ", pubsub);
            return pubsub.asyncIterator(["photo-added"])
        }
            
    },

    newUser: {
        subscribe: (parent, args, {pubsub}) => 
            pubsub.asyncIterator(["user-added"])
    }
}