'use strict';

/**
 * Created by ed on 19.02.17.
 */

const mainCanvas = document.getElementById('mainCanvas');
const mousePositionLabel = document.getElementById('mousePosition');

mainCanvas.height = mainCanvas.parentNode.clientHeight;
mainCanvas.width = mainCanvas.parentNode.clientWidth;

const canvasManager = new CanvasManager(mainCanvas);

const updatePointsList = function () {
    let pointsTable = document.getElementById('pointsList');

    // remove children
    while (pointsTable.firstChild) {
        pointsTable.removeChild(pointsTable.firstChild);
    }

    canvasManager.points.forEach(function (point, index) {
        let row = document.createElement('tr');
        let x = point.x.valueOf();
        let y = point.y.valueOf();
        index = index.valueOf();

        row.innerHTML = `<td>${index + 1}</td><td>${x}</td><td>${y}</td>`;
        row.onclick = function () {
            canvasManager.points.splice(index, 1);
            capture();
            reDraw();
        };
        pointsTable.appendChild(row);
    });

    document.getElementById('pointsNumber').innerHTML = canvasManager.points.length
};

const historyManager = new HistoryManager(canvasManager.points);

const reDraw = function () {
    canvasManager.reDraw();
    updatePointsList();
};

const capture = function () {
    historyManager.capture(canvasManager.points);
};

const undo = function () {
    canvasManager.points = historyManager.undo();
    reDraw();
};

const redo = function () {
    canvasManager.points = historyManager.redo();
    reDraw();
};

const reset = function () {
    canvasManager.points = historyManager.reset();
    reDraw();
};

const clear = function () {
    canvasManager.points = historyManager.clear();
    reDraw();
};

mainCanvas.addEventListener('click', function (e) {
    let pos = canvasManager.getMousePosition(e);
    canvasManager.addPoint(pos.x, pos.y);
    capture();
    reDraw();
});

mainCanvas.addEventListener('mousemove', function (e) {
    let mousePosition = canvasManager.getMousePosition(e);

    mousePositionLabel.innerHTML = `Mouse position: ${mousePosition.x}, ${mousePosition.y}`;
    mousePositionLabel.style.visibility = 'visible';
});

mainCanvas.addEventListener('mouseleave', function (e) {
    mousePositionLabel.style.visibility = 'hidden';
});