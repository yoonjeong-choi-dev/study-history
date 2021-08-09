import React from "react"
import MyFixedSizedList from "./MyFixedSizedList"
import createFakeData from "./createFakeData"

const bigList = createFakeData();

export default function VirtualListExample () {
    return (
        <MyFixedSizedList data={bigList} renderEmpty={<h1>Empty Data!</h1>} />
    )
}