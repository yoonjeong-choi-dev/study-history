window.onload = init;
window.addEventListener("resize", onResize, false);

// Three.js 에서 필요한 필수 요소는 전역 처리
var scene;
var camera;
var renderer;


function onResize() {
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();
    renderer.setSize(window.innerWidth, window.innerHeight);
}


function init() {
    var stats = initFrameStats();

    scene = new THREE.Scene();


    // 카메라 생성
    camera = new THREE.PerspectiveCamera(45, window.innerWidth / window.innerHeight, 0.1, 1000);
    camera.position.set(-35, 30, 25);
    camera.lookAt(new THREE.Vector3(10,0,0));
    scene.add(camera)

    // 렌더러 생성 
    renderer = new THREE.WebGLRenderer();
    renderer.setClearColor(new THREE.Color(0xEEEEEE, 1.0));
    renderer.setSize(window.innerWidth, window.innerHeight);
    renderer.shadowMapEnabled = true;

    // 바닥면 생성
    var planeGeometry = new THREE.PlaneGeometry(60, 20, 1, 1);
    var planeMaterial = new THREE.MeshLambertMaterial({
        color: 0xcccccc
    });

    var plane = new THREE.Mesh(planeGeometry, planeMaterial);
    plane.rotation.x = -0.5 * Math.PI;
    plane.position.set(15, 0, 0);
    plane.receiveShadow = true;
    scene.add(plane);
    


    // 물체 생성
    var cubeGeometry = new THREE.BoxGeometry(4, 4, 4);
    var cubeMaterial = new THREE.MeshLambertMaterial({
        color: 0xff0000
    });

    var cube = new THREE.Mesh(cubeGeometry, cubeMaterial);
    cube.position.set(-4, 3, 0);
    cube.castShadow = true;
    scene.add(cube);


    var sphereGeometry = new THREE.SphereGeometry(4, 20, 20);
    var sphereMaterial = new THREE.MeshLambertMaterial({
        color: 0x777ff
    });

    var sphere = new THREE.Mesh(sphereGeometry, sphereMaterial);
    sphere.position.set(20, 0, 2);
    sphere.castShadow = true;
    scene.add(sphere);

    // 주변광 추가 : 보조 광원
    var ambientColor = "#0c0c0c";
    var ambientLight = new THREE.AmbientLight(ambientColor);
    scene.add(ambientLight);


    // 스포트라이트 광원 추가 : 보조 광원(그림자 추가용)
    var aux_spotLight = new THREE.SpotLight(0xcccccc);
    aux_spotLight.position.set(-40, 30, -10);
    aux_spotLight.lookAt(plane);
    scene.add(aux_spotLight)


    // 메인 스포트라이트 추가
    var spotColor = "#ffffff";
    var spotLight = new THREE.SpotLight(spotColor);
    spotLight.position.set(-40, 60, -10);
    spotLight.castShadow = true;        // 그림자 생성 여부
    spotLight.shadowCameraNear = 2;     // 그림자 처음 거리
    spotLight.shadowCameraFar = 200;    // 그림자 마지막 거리
    spotLight.shadowCameraFov = 30;     // 그림자 시야각
    spotLight.target = plane;           // 스포트라이트가 바라보는 물체
    spotLight.distance = 0;             // 스포트라이트의 거리
    spotLight.angle = 0.4;              // 스포트라이트가 광원에서 얼마자 넓게 퍼져 있는지
    scene.add(spotLight);

    // 메인 스포트라이트가 바라보는 물체를 저장하는 변수
    var targetLight = new THREE.Object3D();
    targetLight.position = new THREE.Vector3(5, 0, 0);

    // 메인 스포트라이트에 해당하는 물체
    var sphereLight = new THREE.SphereGeometry(0.2);
    var sphereLightMaterial = new THREE.MeshBasicMaterial({
        color: 0xac6c25
    });
    var sphereLightMesh = new THREE.Mesh(sphereLight, sphereLightMaterial);
    sphereLightMesh.castShadow = true;

    sphereLightMesh.position = new THREE.Vector3(3, 20, 3);
    scene.add(sphereLightMesh);





    document.getElementById("WebGL-output").appendChild(renderer.domElement);


    // 스포트라이트를 조작하는 컨트롤러
    var stopMovingLight = false;
    var controller = new function () {
        this.rotationSpeed = 0.03;
            this.bouncingSpeed = 0.03;
            this.ambientColor = ambientColor;
            this.spotColor = spotColor;
            this.intensity = 1;
            this.distance = 0;
            this.exponent = 30;
            this.angle = 0.1;
            this.debug = false;
            this.castShadow = true;
            this.onlyShadow = false;
            this.target = "Plane";
            this.stopMovingLight = false;
    }

    var gui = new dat.GUI();
    gui.add(controller, "rotationSpeed", 0, 0.5);
    gui.add(controller, "bouncingSpeed", 0, 0.5);

    // 스포트라이트 색상 설정
    gui.addColor(controller, 'ambientColor').onChange( (e) => {
        ambientLight.color = new THREE.Color(e);
    });

    // 스포트라이트 색상 설정
    gui.addColor(controller, 'spotColor').onChange((e) =>  {
        spotLight.color = new THREE.Color(e);
    });

    // 스포트라이트가 광원에서 얼마자 넓게 퍼져 있는지 설정
    gui.add(controller, 'angle', 0, Math.PI * 2).onChange((e) => {
        spotLight.angle = e;
    });

    // 스포트라이트 세기 설정
    gui.add(controller, 'intensity', 0, 5).onChange((e) => {
        spotLight.intensity = e;
    });

    // 스포트라이트의 거리 설정
    gui.add(controller, 'distance', 0, 200).onChange((e) => {
        spotLight.distance = e;
    });

    // 거리에 따른 스포트라이트의 세기 감소 설정
    gui.add(controller, 'exponent', 0, 100).onChange((e)=> {
        spotLight.exponent = e;
    });

    // 스포트라이트에 대한 그림자 부피를 보이게 하는지 설정
    // castShadow가 참인 경우에만 렌더링된다
    gui.add(controller, 'debug').onChange((e)=> {
        spotLight.shadowCameraVisible = e;
    });

    // 그림자 생성 여부 설정    
    // 중간에 off하는 경우 이전 그림자는 남아 있는다
    gui.add(controller, 'castShadow').onChange((e)=> {
        spotLight.castShadow = e;
    });

    // 장면(scene)에 스포트라이트 자체를 추가할지 여부 설정
    // false : 그림자만 만들뿐, 빛을 비추지 않음
    gui.add(controller, 'onlyShadow').onChange((e)=> {
        spotLight.onlyShadow = e;
    });

    // target 컨트롤러 추가
    gui.add(controller, "target", ["Plane", "Sphere", "Cube"]).onChange((e)=>{
        console.log(e);
        switch (e) {
            case "Plane":
                spotLight.target = plane;
                break;
            case "Sphere":
                spotLight.target = sphere;
                break;
            case "Cube":
                spotLight.target = cube;
                break;
        }
    });

    // 메인 스포트라이트 이동 on/off
    gui.add(controller, "stopMovingLight").onChange((e)=>{
        stopMovingLight = e;
    })




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
    var step = 0;
    var invert = 1;
    var phase = 0;
    function renderScene() {
        // 통계치 업데이트
        stats.update();

        // 컨트롤러 값을 이용하여 물체 운동 업데이트
        cube.rotation.x += controller.rotationSpeed;
        cube.rotation.y += controller.rotationSpeed;
        cube.rotation.z += controller.rotationSpeed;

        step += controller.bouncingSpeed;
        sphere.position.x = 20 + ( 10 * (Math.cos(step)));
        sphere.position.y = 2 + ( 10 * Math.abs(Math.sin(step)));


        // 메인스포트라이트 이동
        if (!stopMovingLight) {
            if (phase > 2 * Math.PI) {
                invert = invert * -1;
                phase -= 2 * Math.PI;
            } else {
                phase += controller.rotationSpeed;
            }
            sphereLightMesh.position.z = +(7 * (Math.sin(phase)));
            sphereLightMesh.position.x = +(14 * (Math.cos(phase)));
            sphereLightMesh.position.y = 10;

            if (invert < 0) {
                var pivot = 14;
                sphereLightMesh.position.x = (invert * (sphereLightMesh.position.x - pivot)) + pivot;
            }

            spotLight.position.copy(sphereLightMesh.position);
        }

        requestAnimationFrame(renderScene);
        renderer.render(scene, camera);
    }

}