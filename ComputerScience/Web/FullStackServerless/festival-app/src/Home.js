import React, { useState, useEffect } from "react";
import { API } from "aws-amplify";
import { listStages } from "./graphql/queries";
import { Link } from "react-router-dom";
import { List } from "antd";

const heading = { fontSize: 44, fontWeight: 300, marginBottom: "5px" }
const stageInfo = { padding: "20px 0px 10px", borderBottom: "2px solid #ddd" }
const infoTitle = { fontWeight: "bold", fontSize: 18 }
const infoHeading = { fontSize: 30, marginBottom: "5px" }
const performerInfo = { fontSize: 24 }


const Home = () => {
    const [stages, setStages] = useState([]);
    const [loading, setLoading] = useState(true);

    const fetchStages = async () => {
        try {
            const data = await API.graphql({
                query: listStages,
                authMode: "AMAZON_COGNITO_USER_POOLS"
            });
            const { data: { listStages: { items } } } = data;
            setLoading(false);
            setStages(items);
        } catch (err) {
            console.error("Fail to fetch stages : ", err);
            setLoading(true);
        }
    }

    useEffect(() => {
        fetchStages();
    }, []);

    return (
        <div>
            <h1 style={heading}>Stages</h1>
            {loading && <h2>Loading...</h2>}
            {
                stages.map(stage => (
                    <div key={stage.id} style={stageInfo}>
                        <p style={infoHeading}>{stage.name}</p>
                        <p style={infoTitle}>Performances</p>
                        <List
                            itemLayout="horizontal"
                            dataSource={stage.performances.items}
                            renderItem={performance => (
                                <List.Item>
                                    <List.Item.Meta
                                        title={<Link style={performerInfo} to={`/performance/${performance.id}`}>{performance.performer}</Link>}
                                        description={performance.time}
                                    />
                                </List.Item>
                            )}
                        />
                    </div>
                ))
            }
        </div>
    );
};

export default Home;