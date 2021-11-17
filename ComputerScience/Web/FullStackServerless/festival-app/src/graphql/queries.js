/* eslint-disable */
// this is an auto generated file. This will be overwritten

export const getStage = /* GraphQL */ `
  query GetStage($id: ID!) {
    getStage(id: $id) {
      id
      name
      createdAt
      updatedAt
      performances {
        items {
          id
          performanceStageId
          productID
          performer
          imageUrl
          description
          time
          createdAt
          updatedAt
        }
        nextToken
      }
    }
  }
`;
export const listStages = /* GraphQL */ `
  query ListStages(
    $filter: ModelStageFilterInput
    $nextToken: String
  ) {
    listStages(filter: $filter, limit: 500, nextToken: $nextToken) {
      items {
        id
        name
        performances {
          items {
            id
            time
            performer
            description
          }
        }
      }
      nextToken
    }
  }
`;
export const getPerformance = /* GraphQL */ `
  query GetPerformance($id: ID!) {
    getPerformance(id: $id) {
      id
      performanceStageId
      productID
      performer
      imageUrl
      description
      time
      createdAt
      updatedAt
      stage {
        id
        name
        createdAt
        updatedAt
        performances {
          nextToken
        }
      }
    }
  }
`;
export const listPerformances = /* GraphQL */ `
  query ListPerformances(
    $filter: ModelPerformanceFilterInput
    $limit: Int
    $nextToken: String
  ) {
    listPerformances(filter: $filter, limit: $limit, nextToken: $nextToken) {
      items {
        id
        performanceStageId
        productID
        performer
        imageUrl
        description
        time
        createdAt
        updatedAt
        stage {
          id
          name
          createdAt
          updatedAt
        }
      }
      nextToken
    }
  }
`;
