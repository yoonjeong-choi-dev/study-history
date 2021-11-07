const Query = require("./Query");
const Mutation = require("./Mutation");
const Subscription = require("./Subscription");
const Type = require("./Type");

// Define resolvers with Root Types
const resolvers = {
  Query,
  Mutation,
  Subscription,
  ...Type
}

module.exports = resolvers