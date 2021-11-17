import React, {useState, useEffect} from "react";
import { useParams } from "react-router-dom";
import { getPerformance } from "./graphql/queries";
import { API } from "aws-amplify";

const Performance = () => {
    const [performance, setPerformance ] = useState(null);
    const [loading, setLoading] = useState(true);

    let { id } = useParams();

    const fetchPerformanceInfo = async () => {
        try{
            const info = await API.graphql({
                query: getPerformance,
                variables: { id },
                authMode: 'AWS_IAM'
            });
            setPerformance(info.data.getPerformance);
            setLoading(false);
        } catch (err){
            console.error(`Fail to fetch info ${id} : `, err);
            setLoading(true);
        }
    }

    useEffect(()=>{
        fetchPerformanceInfo();
    }, []);


    return (
        <div>
            <p>Performance</p>
            { loading && <h3>Loading...</h3>}
            {
                performance && (
                    <div>
                        <h1>Performer : {performance.performer}</h1>
                        <h3>Time : {performance.time}</h3>
                        <p>Description : {performance.description}</p>
                    </div>
                )
            }
        </div>
    );
};

export default Performance;