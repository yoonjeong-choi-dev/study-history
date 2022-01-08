import { useEffect, useState } from "react";

// simple data
const data = {
  '1': {
    'name': 'Yoonjeong',
    'age': 30
  },
  '2': {
    'name': 'YJ',
    'age': 29
  }
};

const getUser = async (id) => {
  return data[id];
}

const useUser = (userId) => {
  const [user, setUser] = useState(null);
  useEffect(() => {
    getUser(userId).then(data=> setUser(data));
  }, [userId]);

  return user;
}

export default useUser;