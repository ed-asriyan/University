'use strict';

/**
 * Created by ed on 19.02.17.
 */

const mainCanvas = document.getElementById('mainCanvas');
const canvasManager = new CanvasManager(mainCanvas, {
    mousePositionLabelVisibility: true,
    gridOpacity: 0.15,
    gridColor: 'black',
    gridStep: 20,
});
