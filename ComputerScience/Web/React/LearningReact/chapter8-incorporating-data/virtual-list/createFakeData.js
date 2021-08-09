import faker from "faker";

const createFakeData = () => {
    const bigList = [...Array(5000)].map(()=>({
        name: faker.name.findName(),
        email: faker.internet.email(),
        avartar: faker.internet.avatar()
    }));

    return bigList;
}

export default createFakeData;