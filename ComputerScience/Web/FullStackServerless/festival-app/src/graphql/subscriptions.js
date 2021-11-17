/* eslint-disable */
// this is an auto generated file. This will be overwritten

export const onCreateStage = /* GraphQL */ `
  subscription OnCreateStage {
    onCreateStage {
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
export const onUpdateStage = /* GraphQL */ `
  subscription OnUpdateStage {
    onUpdateStage {
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
export const onDeleteStage = /* GraphQL */ `
  subscription OnDeleteStage {
    onDeleteStage {
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
export const onCreatePerformance = /* GraphQL */ `
  subscription OnCreatePerformance {
    onCreatePerformance {
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
export const onUpdatePerformance = /* GraphQL */ `
  subscription OnUpdatePerformance {
    onUpdatePerformance {
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
export const onDeletePerformance = /* GraphQL */ `
  subscription OnDeletePerformance {
    onDeletePerformance {
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
