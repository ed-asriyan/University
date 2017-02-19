'use strict';

/**
 * Created by ed on 19.02.17.
 */

class HistoryManager {
    constructor() {
        this._history = [];
        this._position = 0;
    }

    capture(obj) {
        this._history.length = this._position;
        this._history.push(obj);
        ++this._position;
    }

    undo() {
        if (this._position > 0) {
            return this._history[--this._position];
        } else {
            return null;
        }
    }

    redo() {
        if (this._position < this._history.length) {
            return this._history[++this._position];
        } else {
            return null;
        }
    }
}