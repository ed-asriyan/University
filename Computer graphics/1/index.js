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
        row.point = point;

        // the first column
        let indexCol = document.createElement('td');
        let indexLabel = document.createElement('label');
        indexLabel.innerHTML = index.valueOf();
        indexCol.appendChild(indexLabel);
        row.appendChild(indexCol);

        // the second column
        let xCol = document.createElement('td');
        xCol.innerHTML = point.x.valueOf();
        row.appendChild(xCol);

        // the third column
        let yCol = document.createElement('td');
        yCol.innerHTML = point.y.valueOf();
        row.appendChild(yCol);

        // remove button
        let removeCol = document.createElement('td');
        let removeBtn = document.createElement('button');
        removeBtn.type = 'button';
        removeBtn.className = 'btn btn-danger';
        removeBtn.innerHTML = 'Remove';
        removeBtn.addEventListener('click', function () {
            // remove point from canvasManager
            canvasManager.points.splice(canvasManager.points.indexOf(this.parentNode.parentNode.point), 1);
            capture();
            canvasManager.reDraw();
        });
        row.addEventListener('mouseover', function () {
            this.point.radius = 4;
            this.point.color = 'red';
            canvasManager.reDraw();
        });
        row.addEventListener('mouseout', function () {
            this.point.radius = 2.5;
            this.point.color = 'black';
            reDraw();
        });
        removeCol.appendChild(removeBtn);
        row.appendChild(removeCol);

        pointsTable.appendChild(row);
    });

    document.getElementById('pointsNumber').innerHTML = canvasManager.points.length
};

const historyManager = new HistoryManager(canvasManager.points);

const add = function () {
    let pointsInput = document.getElementById('pointsInput');
    let pos = pointsInput.value.split(',');
    let x = parseInt(pos[0]);
    let y = parseInt(pos[1]);
    if (x && y) {
        canvasManager.addPoint(x, y);
        capture();
        reDraw();
        pointsInput.value = '';
    }
};

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

const clean = function () {
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