window.onload = init;
window.addEventListener("resize", onResize, false);

// Three.js 에서 필요한 필수 요소는 전역 처리
var scene;
var camera;
var renderer;

// Step 7 : resize
function onResize() {
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();
    renderer.setSize(window.innerWidth, window.innerHeight);
}


function init() {
    var stats = initFrameStats();

    scene = new THREE.Scene();
    //scene.fog = new THREE.Fog(0xfffff,  0.015, 100);

    // 카메라 생성
    camera = new THREE.PerspectiveCamera(45, window.innerWidth / window.innerHeight, 0.1, 1000);
    camera.position.set(-20, 25, 20);
    camera.lookAt(new THREE.Vector3(5, 0, 0));
    scene.add(camera)

    // 렌더러 생성 
    renderer = new THREE.WebGLRenderer();
    renderer.setClearColor(new THREE.Color(0xEEEEEE, 1.0));
    renderer.setSize(window.innerWidth, window.innerHeight);
    renderer.shadowMapEnabled = true;

    // 바닥면 생성
    var planeGeometry = new THREE.PlaneGeometry(60, 40, 1, 1);
    var planeMaterial = new THREE.MeshLambertMaterial({
        color: 0xffffff
    });

    var plane = new THREE.Mesh(planeGeometry, planeMaterial);
    plane.rotation.x = -0.5 * Math.PI;
    plane.position.set(0, 0, 0);
    plane.receiveShadow = true;
    scene.add(plane);

    // 스포트라이트 추가
    var spotLight = new THREE.SpotLight(0xffffff);
    spotLight.position.set(-40, 60, 10);
    spotLight.castShadow = true;
    scene.add(spotLight);

    // 주변광 추가
    var ambientLight = new THREE.AmbientLight(0x0c0c0c);
    scene.add(ambientLight);

    document.getElementById("WebGL-output").appendChild(renderer.domElement);



    // 커스텀 육면체 객체를 위한 정점 및 면 설정
    var vertices = [
        new THREE.Vector3(1, 3, 1),
        new THREE.Vector3(1, 3, -1),
        new THREE.Vector3(1, -1, 1),
        new THREE.Vector3(1, -1, -1),
        new THREE.Vector3(-1, 3, -1),
        new THREE.Vector3(-1, 3, 1),
        new THREE.Vector3(-1, -1, -1),
        new THREE.Vector3(-1, -1, 1)
    ];

    var faces = [
        new THREE.Face3(0, 2, 1),
        new THREE.Face3(2, 3, 1),
        new THREE.Face3(4, 6, 5),
        new THREE.Face3(6, 7, 5),
        new THREE.Face3(4, 5, 1),
        new THREE.Face3(5, 0, 1),
        new THREE.Face3(7, 6, 2),
        new THREE.Face3(6, 3, 2),
        new THREE.Face3(5, 7, 0),
        new THREE.Face3(7, 2, 0),
        new THREE.Face3(1, 3, 4),
        new THREE.Face3(3, 6, 4),
    ];

    // 기설정된 정점 및 면으로 구성된 지오메트리 생성
    var geometry = new THREE.Geometry();
    geometry.vertices = vertices;
    geometry.faces = faces;
    geometry.computeFaceNormals();

    // 머티리얼 설정
    var materials = [
        new THREE.MeshLambertMaterial({
            opacity: 0.6,
            color: 0x44ff44,
            transparent: true
        }),
        new THREE.MeshBasicMaterial({
            color: 0x00000,
            wireframe: true
        })
    ];

    // 여러 머티리얼에 대한 메시 생성 : 각 머티리얼이 적용된 메시 오브젝트 생성
    var mesh = THREE.SceneUtils.createMultiMaterialObject(geometry, materials);

    // 각 메시 오브젝트에 대한 그림자 설정
    mesh.children.forEach((m) => {
        m.castShadow = true;
    });

    scene.add(mesh);


    // 정점 복제 함수
    function copyCustomHexadron(x, y, z) {
        let control_point = new function () {
            this.x = x;
            this.y = y;
            this.z = z;
        }

        return control_point;
    }

    // 커스텀 육면체를 복사하기 위한 정점 리스트
    var controlPoints = [];
    controlPoints.push(copyCustomHexadron(3, 5, 3));
    controlPoints.push(copyCustomHexadron(3, 5, 0));
    controlPoints.push(copyCustomHexadron(3, 0, 3));
    controlPoints.push(copyCustomHexadron(3, 0, 0));
    controlPoints.push(copyCustomHexadron(0, 5, 0));
    controlPoints.push(copyCustomHexadron(0, 5, 3));
    controlPoints.push(copyCustomHexadron(0, 0, 0));
    controlPoints.push(copyCustomHexadron(0, 0, 3));

    // 정점을 조작하는 컨트롤러 gui
    var gui = new dat.GUI();
    gui.add(new function () {
        this.clone = function () {
            let cloneGeometry = mesh.children[0].geometry.clone();
            let clonseMaterials = [
                new THREE.MeshLambertMaterial({
                    opacity: 0.6,
                    color: 0xff44ff,
                    transparent: true
                }),
                new THREE.MeshBasicMaterial({
                    color: 0x000000, wireframe: true
                })
            ];

            let cloneMesh = THREE.SceneUtils.createMultiMaterialObject(cloneGeometry, clonseMaterials);
            cloneMesh.children.forEach((m) => {
                m.castShadow = true;
            });

            cloneMesh.translateX(5);
            cloneMesh.translateZ(5);
            cloneMesh.name = "clone";
            scene.remove(scene.getObjectByName("clone"));    // 이전에 만든 복제 메시 삭제
            scene.add(cloneMesh);
        }
    }, "clone");

    // gui에 추가할 메뉴 설정
    for (let i = 0; i < controlPoints.length; i++) {
        f1 = gui.addFolder("Vertices" + (i));
        f1.add(controlPoints[i], "x", -10, 10);
        f1.add(controlPoints[i], "y", -10, 10);
        f1.add(controlPoints[i], "z", -10, 10);
    }



    renderScene();



    // 프레임 확인 함수
    function initFrameStats() {
        var stats = new Stats();
        stats.setMode(0);   // 0: 프레임 확인용
        stats.domElement.style.position = "absolute";
        stats.domElement.style.left = "0px";
        stats.domElement.style.top = "0px";
        document.getElementById("Stats-output").appendChild(stats.domElement);

        return stats;
    }

    // 렌더링 처리 함수
    function renderScene() {
        // 통계치 업데이트
        stats.update();

        var vertices = [];
        for (var i = 0; i < controlPoints.length; i++) {
            vertices.push(new THREE.Vector3(controlPoints[i].x, controlPoints[i].y, controlPoints[i].z));
        }

        // 지오메트리(정점) 변경
        // 면은 정점 배열의 index들로 구성되어 있어 변경 필요 X
        mesh.children.forEach(function (e) {
            e.geometry.vertices = vertices;
            e.geometry.verticesNeedUpdate = true;   // 정점들이 업데이트 되었다고 알려줘야 한다
            e.geometry.computeFaceNormals();        // 정점으로 구성된 면들의 법선 벡터를 다시 계산
        });

        requestAnimationFrame(renderScene);
        renderer.render(scene, camera);
    }

}