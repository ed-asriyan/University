'use strict';

/**
 * Created by ed on 12.03.17.
 */

const onReset = function () {
    resetImage();
};

const onRedraw = function () {
    reDraw();
};

const onMoveApply = function () {
    let x = +xMoveInput.value;
    let y = +yMoveInput.value;

    if (!isFinite(x)) {
        // todo:
    }
    if (!isFinite(y)) {
        // todo:
    }

    moveImage({x: x, y: y});
};

const onScaleApply = function () {
    let x = +xScaleInput.value;
    let y = +yScaleInput.value;
    let xCenter = +xScaleCenterInput.value;
    let yCenter = +yScaleCenterInput.value;

    if (!isFinite(x)) {
        // todo:
    }
    if (!isFinite(y)) {
        // todo:
    }

    scaleImage({x: x, y: y, center: new Point(xCenter, yCenter)});
};

const onRotationApply = function () {
    let angle = +rotationInput.value;
    let xCenter = +xRotationCenterInput.value;
    let yCenter = +yRotationCenterInput.value;

    if (!isFinite(xCenter)) {
        // todo:
    }
    if (!isFinite(yCenter)) {
        // todo:
    }
    if (!isFinite(angle)) {
        // todo:
    }

    rotateImage({angle: angle, center: new Point(xCenter, yCenter)});
};

resetButton.addEventListener('click', onReset);
redrawButton.addEventListener('click', onRedraw);
moveButton.addEventListener('click', onMoveApply);
scaleButton.addEventListener('click', onScaleApply);
rotationButton.addEventListener('click', onRotationApply);