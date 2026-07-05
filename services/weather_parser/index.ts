import * as Types from './types.ts';
import { fetchWeather } from './apiController.ts';
import { writeData } from './fileController.ts';

async function main(): Promise<number> {
  let Seoul: Types.Coord = {
    lat: 37.5665,
    lon: 126.9780,
  }

  const data = await fetchWeather(Seoul);
  if (!data.ok) return 1;

  writeData(data);
  
  return 0;
}

process.exit(await main());
