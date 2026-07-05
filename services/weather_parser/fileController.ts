import { rename } from "node:fs/promises";

import * as Types from './types.ts';

export function writeData(data: Types.OpenWeatherAPIResponse): void {
  const OUTPUT_PATH = "data/weather.json";
  const TMP_PATH = OUTPUT_PATH + ".tmp";

  const json = JSON.stringify(data, null, 2);

  Bun.write(TMP_PATH, json);
  rename(TMP_PATH, OUTPUT_PATH);
}
