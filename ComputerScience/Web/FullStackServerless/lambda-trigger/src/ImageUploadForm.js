import React, {useState, useEffect} from "react";
import { Storage } from "aws-amplify";
import {parse, v4 as uuid } from "uuid";

const ImageUploadForm = () => {
    const [images, setImages] = useState([]);

    const fetchImage = async () => {
        // 해당 버킷에서 사진 리스트 추출
        const files = await Storage.list("");

        // 각 파일들의 키를 이용하여 signed_url 가져오기
        const signedFiles = await Promise.all(files.map(
            async file => {
                const signedFile = await Storage.get(file.key);
                return signedFile
            }
        ));

        setImages(signedFiles);
    }

    useEffect(()=>{
        fetchImage();
    },[])

    // 파일 input 폼에서 파일 가져오기
    const onChange = async (e) => {
        const file = e.target.files[0];
        const parsedFile = file.name.split(".");
        const filetype = parsedFile[parsedFile.length -1 ]
        await Storage.put(`${uuid()}.${filetype}`, file);

        // 업로드 후 다시 리스트 가져옴
        fetchImage();
    }

    return (
        <div>
            <input type="file" onChange={onChange}/>
            {
                images.map(image => (
                    <img src={image} key={image} style={{width:500}}/>
                ))
            }
        </div>
    )
}

export default ImageUploadForm;