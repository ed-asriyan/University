'use strict';

/**
 * Created by ed on 03.03.17.
 */

const onAddButtonClick = function (e) {
    let pointsInput = document.getElementById('pointsInput');
    let pos = pointsInput.value.split(',');
    let x = parseInt(pos[0]);
    let y = parseInt(pos[1]);
    if (isFinite(x) && isFinite(y)) {
        let point = new Point(x, y);
        createPoint(point);
        updateTrianglesList();
        pointsInput.value = '';
    }
};

const onCanvasMouseClick = function (e) {
    let point = canvasManager.getMousePosition(e);

    createPoint(point);
    updateTrianglesList();
};

const onCanvasMouseMove = function (e) {
    let point = canvasManager.getMousePosition(e);

    mousePositionLabel.innerHTML = `Mouse position: ${Math.round(point.x)}, ${Math.round(point.y)}`;
    mousePositionLabel.style.visibility = 'visible';
};

const onCavasMouseLeave = function () {
    mousePositionLabel.style.visibility = 'hidden';
};

const onPointRowMouseOver = function () {
    drawHighlightedPoint(this.point);
};

const onPointRowMouseOut = function () {
    reDrawPoints();
};

const onRemovePointButtonClick = function () {
    let point = this.point;
    destroyPoint(point);
    updateTrianglesList();
};

const onTriangleRowMounseOver = function () {
    drawTriangle(this.triangle);
};

const onTriangleRowMounseOut = function () {
    reDrawPoints();
};

const onUndo = function () {
    undo();
};

const onRedo = function () {
    redo();
};

const onReset = function () {
    reset();
};

const onClean = function () {
    clean();
};

const onResize = function () {
    resize();
    reDrawPoints();
};

const onResizeOrtho = function () {
    resize(true);
    reDrawPoints();
};

const onResetSize = function () {
    resetSize();
    reDrawPoints();
};