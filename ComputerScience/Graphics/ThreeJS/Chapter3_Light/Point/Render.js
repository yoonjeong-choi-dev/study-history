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
    var spotLight = new THREE.SpotLight(0xffffff);
    spotLight.position.set(-40, 60, -10);
    spotLight.castShadow = true;
    scene.add(spotLight)


    // 점광원 추가
    var pointColor = "#ccffcc";
    var pointLight = new THREE.PointLight(pointColor);
    pointLight.distance = 100;
    scene.add(pointLight);

    // 점광원을 표현하는 객체
    var sphereLight = new THREE.SphereGeometry(0.2);
    var sphereLightMaterial = new THREE.MeshBasicMaterial({color: 0xac6c25});
    var sphereLightMesh = new THREE.Mesh(sphereLight, sphereLightMaterial);
    sphereLightMesh.castShadow = true;

    sphereLightMesh.position = new THREE.Vector3(3, 0, 3);
    scene.add(sphereLightMesh);

    
    document.getElementById("WebGL-output").appendChild(renderer.domElement);


    // 점광원을 조작하는 컨트롤러
    var controller = new function () {
        this.rotationSpeed = 0.02;
        this.bouncingSpeed = 0.03;
        this.ambientColor = ambientColor;
        this.pointColor = pointColor;
        this.intensity = pointLight.intensity;
        this.distance = pointLight.distance;
    }

    var gui = new dat.GUI();
    gui.add(controller, "rotationSpeed", 0, 0.5);
    gui.add(controller, "bouncingSpeed", 0, 0.5);
    gui.addColor(controller, "ambientColor").onChange((e)=>{
        ambientLight.color = new THREE.Color(e);
    });
    gui.addColor(controller, "pointColor").onChange((e)=>{
        pointLight.color = new THREE.Color(e);
    });
    gui.add(controller, "intensity", 0, 3).onChange((e) => {
        pointLight.intensity = e;
    })
    gui.add(controller, "distance", 0, 100).onChange((e)=>{
        spotLight.distance = e;
    });
   


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

        // 점광원 위치 변경
        // phase의 범위는 [0, 2*PI]
        // phase가 한바퀴 돌때마다 invert를 통해 점광원의 이동 방향(x)축 이동을 반대방향으로 바꾼다
        // => 8자형으로 이동
        if (phase > 2 * Math.PI) {
            invert = invert * -1;
            phase -= 2 * Math.PI;
        } else {
            phase += controller.rotationSpeed;
        }

        sphereLightMesh.position.z = +(7 * (Math.sin(phase)));
        sphereLightMesh.position.x = +(14 * (Math.cos(phase)));
        sphereLightMesh.position.y = 5;

        if (invert < 0) {
            var pivot = 14;
            sphereLightMesh.position.x = (invert * (sphereLightMesh.position.x - pivot)) + pivot;
        }

        pointLight.position.copy(sphereLightMesh.position);


        requestAnimationFrame(renderScene);
        renderer.render(scene, camera);
    }

}