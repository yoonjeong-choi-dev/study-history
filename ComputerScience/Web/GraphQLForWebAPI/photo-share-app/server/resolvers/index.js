const Query = require('./Query')
const Mutation = require('./Mutation')
const Type = require('./Type')

// Define resolvers with Root Types
const resolvers = {
  Query,
  Mutation,
  ...Type
}

module.exports = resolvers