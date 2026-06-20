/**
 * @format
 */

import App from '../App';

import {it, expect} from '@jest/globals';

it('exports the App component', () => {
  expect(typeof App).toBe('function');
});
