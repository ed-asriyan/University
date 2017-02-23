'use strict';

/**
 * Created by ed on 19.02.17.
 */

class HistoryManager {
    constructor(initial) {
        this._history = [initial.slice()];
        this._position = 0;
    }

    capture(obj) {
        return this._history[this._history.length = ++this._position] = obj.slice();
    }

    undo() {
        if (this._position > 0) {
            return this._history[--this._position].slice();
        }
    }

    redo() {
        if (this._position + 1 < this._history.length) {
            return this._history[++this._position].slice();
        }
    }

    reset() {
        this._history.length = 1;
        return this._history[this._position = 0].slice();
    }

    clear() {
        return this.capture(this._history[0]).slice();
    }
}