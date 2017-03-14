'use strict';

/**
 * Created by ed on 11.03.17.
 */

//
// XML elements
//
const mainCanvas = document.getElementById('mainCanvas');

const resetButton = document.getElementById('reset');

const xMoveInput = document.getElementById('xMove');
const yMoveInput = document.getElementById('yMove');
const moveButton = document.getElementById('moveBtn');

const xScaleInput = document.getElementById('xScale');
const yScaleInput = document.getElementById('yScale');
const xScaleCenterInput = document.getElementById('xScaleCenter');
const yScaleCenterInput = document.getElementById('yScaleCenter');
const scaleButton = document.getElementById('scaleBtn');

const xRotationCenterInput = document.getElementById('xRotationCenter');
const yRotationCenterInput = document.getElementById('yRotationCenter');
const rotationInput = document.getElementById('rotation');
const rotationButton = document.getElementById('rotationBtn');

const canvasManager = new CanvasManager(mainCanvas);

let imagePoints = [];

//
// Functions
//
const reDraw = function () {
    canvasManager.clear();
    canvasManager.drawGrid();
    imagePoints.forEach(function (point) {
        canvasManager.drawPoint({
            point: point
        });
    });
};

const resetPoints = function (solver = new Solver(100), options) {
    imagePoints = [...solver.allPointsSequence(options)];
};

const resetOptions = function () {
    xMoveInput.value = 0;
    yMoveInput.value = 0;

    xScaleInput.value = 1;
    yScaleInput.value = 1;
    xScaleCenterInput.value = 0;
    yScaleCenterInput.value = 0;

    xRotationCenterInput.value = 0;
    yRotationCenterInput.value = 0;
    rotationInput.value = 0;
};

const movePoints = function (options) {
    imagePoints.forEach(function (point, index) {
        imagePoints[index] = transformations.move(point, options);
    });
    reDraw();
};

const scalePoints = function (options) {
    imagePoints.forEach(function (point, index) {
        imagePoints[index] = transformations.scale(point, options);
    });
    reDraw();
};

const rotatePoints = function (options = {angle: 0, center: new Point(0, 0)}) {
    imagePoints.forEach(function (point, index) {
        imagePoints[index] = transformations.rotate(point, options);
    });
    reDraw();
};

const resetCamera = function () {
    mainCanvas.width = mainCanvas.parentNode.clientWidth;
    mainCanvas.height = Math.min(window.innerHeight - mainCanvas.getBoundingClientRect().top - 10, 720);

    canvasManager.cameraOffset = {
        x: Math.round(mainCanvas.width / 2),
        y: Math.round(mainCanvas.height / 2)
    };
    canvasManager.cameraScale = {
        x: 1,
        y: 1,
        center: new Point(0, 0)
    };
    canvasManager.cameraRotation = {
        angle: 0,
        center: new Point(0, 0)
    };

    reDraw();
};

const moveCamera = function (options) {
    canvasManager.moveCamera(options);
    reDraw();
};

//
// XML elements initialization
//
resetPoints();
resetCamera();
resetOptions();
reDraw();


