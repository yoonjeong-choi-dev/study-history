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
    scene.fog = new THREE.Fog(0xaaaaaa, 0.010, 200);
    

    // 카메라 생성
    camera = new THREE.PerspectiveCamera(45, window.innerWidth / window.innerHeight, 0.1, 1000);
    camera.position.set(-20, 15, 45);
    camera.lookAt(new THREE.Vector3(10, 0, 0));
    scene.add(camera)

    // 렌더러 생성 
    renderer = new THREE.WebGLRenderer();
    renderer.setClearColor(new THREE.Color(0xaaaaff, 1.0));
    renderer.setSize(window.innerWidth, window.innerHeight);
    renderer.shadowMapEnabled = true;

    // 바닥면의 텍스처 로드
    var textureGrass = THREE.ImageUtils.loadTexture("assets/textures/ground/grasslight-big.jpg");
    textureGrass.wrapS = THREE.RepeatWrapping;
    textureGrass.wrapT = THREE.RepeatWrapping;
    textureGrass.repeat.set(4, 4);

    // 바닥면 생성
    var planeGeometry = new THREE.PlaneGeometry(1000, 200, 20, 20);
    var planeMaterial = new THREE.MeshLambertMaterial({ map: textureGrass });

    var plane = new THREE.Mesh(planeGeometry, planeMaterial);
    plane.rotation.x = -0.5 * Math.PI;
    plane.position.set(15, 0, 0);
    plane.receiveShadow = true;
    scene.add(plane);



    // 물체 생성
    var cubeGeometry = new THREE.BoxGeometry(4, 4, 4);
    var cubeMaterial = new THREE.MeshLambertMaterial({
        color: 0xff3333
    });

    var cube = new THREE.Mesh(cubeGeometry, cubeMaterial);
    cube.position.set(-4, 3, 0);
    cube.castShadow = true;
    scene.add(cube);


    var sphereGeometry = new THREE.SphereGeometry(4, 25, 25);
    var sphereMaterial = new THREE.MeshLambertMaterial({
        color: 0x7777ff
    });

    var sphere = new THREE.Mesh(sphereGeometry, sphereMaterial);
    sphere.position.set(10, 5, 10);
    sphere.castShadow = true;
    scene.add(sphere);


    // hemisphere light 생성 : (지면 색상, 광원 색상, 광원 강도)
    var hemiLight = new THREE.HemisphereLight(0x0000ff, 0x00ff00, 0.6);
    hemiLight.position.set(0, 500, 0);
    scene.add(hemiLight);




    // 스포트라이트 광원 추가 : 태양 시뮬레이션 광원
    var spotLight0 = new THREE.SpotLight(0xcccccc);
    spotLight0.position.set(-40, 60, -10);
    spotLight0.lookAt(plane);
    scene.add(spotLight0);

    // 방향성 광원 추가 : 태양 시뮬레이션 광원
    var dirColor = "#ffffff";
    var dirLight = new THREE.DirectionalLight(dirColor);
    dirLight.position.set(30,10,-50);
    dirLight.target = plane;
    dirLight.castShadow = true;
    dirLight.shadowCameraNear = 0.1;
    dirLight.shadowCameraFar = 200;
    dirLight.shadowCameraLeft = -50;
    dirLight.shadowCameraRight = 50;
    dirLight.shadowCameraTop = 50;
    dirLight.shadowCameraBottom = -50;
    dirLight.shadowMapWidth = 2048;
    dirLight.shadowMapHeight = 2048;
    scene.add(dirLight);



    document.getElementById("WebGL-output").appendChild(renderer.domElement);


    // 스포트라이트를 조작하는 컨트롤러
    var stopMoving = false;
    var controller = new function () {
        this.rotationSpeed = 0.03;
        this.bouncingSpeed = 0.03;

        this.HemisphereLight = true;
        this.skyColor = 0x0000ff;
        this.groundColor = 0x00ff00;
        this.intensity = 0.6;

        this.stopMoving = stopMoving;
    }

    var gui = new dat.GUI();
    gui.add(controller, "rotationSpeed", 0, 0.5);
    gui.add(controller, "bouncingSpeed", 0, 0.5);


    // 효과 on/off
    gui.add(controller, "HemisphereLight").onChange((e) => {
        if (!e) {
            hemiLight.intensity = 0
        }
        else {
            hemiLight.intensity = controller.intensity;
        }
    });

    gui.addColor(controller, 'groundColor').onChange(function (e) {
        hemiLight.groundColor = new THREE.Color(e);
    });
    gui.addColor(controller, 'skyColor').onChange(function (e) {
        hemiLight.color = new THREE.Color(e);
    });
    gui.add(controller, 'intensity', 0, 5).onChange(function (e) {
        hemiLight.intensity = e;
    });

    // 물체 움직임 on/off
    gui.add(controller, "stopMoving").onChange((e) => {
        stopMoving = e;
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
    function renderScene() {
        // 통계치 업데이트
        stats.update();

        // 컨트롤러 값을 이용하여 물체 운동 업데이트
        if (!stopMoving) {
            cube.rotation.x += controller.rotationSpeed;
            cube.rotation.y += controller.rotationSpeed;
            cube.rotation.z += controller.rotationSpeed;

            step += controller.bouncingSpeed;
            sphere.position.x = 20 + (10 * (Math.cos(step)));
            sphere.position.y = 2 + (10 * Math.abs(Math.sin(step)));
        }

        requestAnimationFrame(renderScene);
        renderer.render(scene, camera);
    }

}