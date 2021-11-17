import { ModelInit, MutableModel, PersistentModelConstructor } from "@aws-amplify/datastore";





type MessageMetaData = {
  readOnlyFields: 'updatedAt';
}

export declare class Message {
  readonly id: string;
  readonly user: string;
  readonly title: string;
  readonly color?: string;
  readonly image?: string;
  readonly createdAt?: string;
  readonly updatedAt?: string;
  constructor(init: ModelInit<Message, MessageMetaData>);
  static copyOf(source: Message, mutator: (draft: MutableModel<Message, MessageMetaData>) => MutableModel<Message, MessageMetaData> | void): Message;
}