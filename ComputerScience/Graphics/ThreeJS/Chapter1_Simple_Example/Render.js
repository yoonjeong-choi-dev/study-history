window.onload = init;
window.addEventListener("resize", onResize, false);

// Three.js 에서 필요한 필수 요소는 전역 처리
var scene;
var camera;
var renderer;

// Step 7 : resize
function onResize(){
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();
    renderer.setSize(window.innerWidth, window.innerHeight);
}


function init(){
    // Step 5 : Frame Stats
    var stats = initFrameStats();

    // scene : 렌더링할 모든 객체와 사용할 모든 광원을 저장하는데 쓰이는 컨테이너
    scene = new THREE.Scene();
    
    // renderer : scene객체가 camera 객체의 각도에 따라 브라우저에 어떻게 보이는지 산출하는 역할
    renderer = new THREE.WebGLRenderer();   // GPU 사용
    renderer.setClearColor(new THREE.Color(0xEEEEEE, 1.0));
    renderer.setSize(window.innerWidth, window.innerHeight);

    var axes = new THREE.AxisHelper(20);
    scene.add(axes);


    // Step 1 : 물체 생성
    var planeGeometry = new THREE.PlaneGeometry(60, 20, 1, 1);
    var planeMaterial = new THREE.MeshLambertMaterial({
        color: 0xcccccc
    });

    var plane = new THREE.Mesh(planeGeometry, planeMaterial);
    plane.rotation.x = -0.5*Math.PI;
    plane.position.set(15, 0, 0);
    scene.add(plane);

    var cubeGeometry = new THREE.BoxGeometry(4, 4, 4);
    var cubeMaterial = new THREE.MeshLambertMaterial({
        color: 0xff0000
    });

    var cube = new THREE.Mesh(cubeGeometry, cubeMaterial);
    cube.position.set(-4, 3, 0);
    scene.add(cube);

    var sphereGeometry = new THREE.SphereGeometry(4, 20, 20);
    var sphereMaterial = new THREE.MeshLambertMaterial({
        color: 0x777ff
    });

    var sphere = new THREE.Mesh(sphereGeometry, sphereMaterial);
    sphere.position.set(20, 4, 2);
    scene.add(sphere);


    // Step 2 : 광원 설정
    var spotLight = new THREE.SpotLight(0xffffff);
    spotLight.position.set(-40, 60, -10);
    scene.add(spotLight);

    // Step 3 : 그림자 활성화
    renderer.shadowMapEnabled = true;
    plane.receiveShadow = true;
    cube.castShadow = true;
    sphere.castShadow = true;
    spotLight.castShadow = true;

    
    // camera : 장면을 렌더링했을 때 어떻게 보여질 것인지 정의
    camera = new THREE.PerspectiveCamera(45, window.innerWidth/window.innerHeight, 0.1, 1000);

    camera.position.x = -30;
    camera.position.y = 40;
    camera.position.z = 30;
    camera.lookAt(scene.position)

    document.getElementById("WebGL-output").appendChild(renderer.domElement);


    // Step 6 : animation controller
    var step = 0;
    var controls = new function(){
        this.rotationSpeed = 0.02;
        this.bouncingSpeed = 0.03;
    }
    var gui = new dat.GUI();
    gui.add(controls, "rotationSpeed", 0, 0.5);
    gui.add(controls, "bouncingSpeed", 0, 0.5);

    // Step 5 : Animation
    renderScene();

    // 프레임 확인 함수
    function initFrameStats(){
        var stats = new Stats();
        stats.setMode(0);   // 0: 프레임 확인용
        stats.domElement.style.position = "absolute";
        stats.domElement.style.left = "0px";
        stats.domElement.style.top = "0px";
        document.getElementById("Stats-output").appendChild(stats.domElement);

        return stats;
    }

    // 렌더링 처리 함수
    function renderScene(){
        // 통계치 업데이트
        stats.update();

        // 물체 업데이트
        cube.rotation.x += controls.rotationSpeed;
        cube.rotation.y += controls.rotationSpeed;
        cube.rotation.z += controls.rotationSpeed;
        step += controls.bouncingSpeed;
        sphere.position.x = 20 + ( 10 * (Math.cos(step)));
        sphere.position.y = 2 + ( 10 * Math.abs(Math.sin(step)));

        requestAnimationFrame(renderScene);
        renderer.render(scene, camera);
    }

}