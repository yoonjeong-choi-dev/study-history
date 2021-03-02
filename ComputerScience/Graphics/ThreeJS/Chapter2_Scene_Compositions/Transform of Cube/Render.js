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
    camera.position.set(-30, 40, 30);
    camera.lookAt(scene.position);
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

    // 물체 생성
    var cubeGeometry = new THREE.BoxGeometry(5, 8, 3);
    var cubeMaterial = new THREE.MeshLambertMaterial({ color: 0x44ff44 });
    var cube = new THREE.Mesh(cubeGeometry, cubeMaterial);
    cube.position.y = 4;
    cube.castShadow = true;
    scene.add(cube);


    // 스포트라이트 광원 추가
    var spotLight = new THREE.SpotLight(0xffffff);
    spotLight.position.set(-40, 60, 020);
    spotLight.castShadow = true;
    scene.add(spotLight)

    // 주변광 추가
    var ambientLight = new THREE.AmbientLight(0x292929);
    scene.add(ambientLight);

    document.getElementById("WebGL-output").appendChild(renderer.domElement);


    // 육면체 조작하는 컨트롤러
    var controller = new function () {
        this.scaleX = 1;
        this.scaleY = 1;
        this.scaleZ = 1;

        this.positionX = 0;
        this.positionY = 4;
        this.positionZ = 0;

        this.rotationX = 0;
        this.rotationY = 0;
        this.rotationZ = 0;
        this.scale = 1;

        this.translateX = 0;
        this.translateY = 0;
        this.translateZ = 0;

        this.visible = true;

        this.translate = function (){
            cube.translateX(this.translateX);
            cube.translateY(this.translateY);
            cube.translateZ(this.translateZ);

            this.positionX = cube.position.x;
            this.positionY = cube.position.y;
            this.positionZ = cube.position.z;
        }

    }

    var gui = new dat.GUI();

    // Scale
    guiScale = gui.addFolder("scale");
    guiScale.add(controller, "scaleX", 0, 5);
    guiScale.add(controller, "scaleY", 0, 5);
    guiScale.add(controller, "scaleZ", 0, 5);

    // Position
    guiPosition = gui.addFolder("position");
    guiPosition.add(controller, "positionX", -10, 10);
    guiPosition.add(controller, "positionY", -4, 20);
    guiPosition.add(controller, "positionZ", -10, 10);

    // rotation
    guiRotation = gui.addFolder("rotation");
    guiRotation.add(controller, "rotationX", -4, 4);
    guiRotation.add(controller, "rotationY", -4, 4);
    guiRotation.add(controller, "rotationZ", -4, 4);

    // translate
    guiTranslate = gui.addFolder("translate");
    guiTranslate.add(controller, "translateX", -4, 4);
    guiTranslate.add(controller, "translateY", -4, 4);
    guiTranslate.add(controller, "translateZ", -4, 4);
    guiTranslate.add(controller, "translate");

    // visible
    gui.add(controller, "visible");



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

        // 컨트롤러 값을 이용하여 큐브 업데이트
        cube.position.set(controller.positionX, controller.positionY, controller.positionZ);
        cube.rotation.set(controller.rotationX, controller.rotationY, controller.rotationZ);
        cube.scale.set(controller.scaleX, controller.scaleY, controller.scaleZ);
        cube.visible = controller.visible;


        requestAnimationFrame(renderScene);
        renderer.render(scene, camera);
    }

}