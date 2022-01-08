import React from 'react';
import useUser from './useUser';

export default function User({userId}) {
  const user = useUser(userId);

  if (!user) return (
    <div>
      <h3>Loading..</h3>
    </div>
  );

  return (
    <div>
      <h3>Name : {user.name}</h3>
      <h3>Age: {user.age}</h3>
    </div>
  );
}