import Config from './config.json'
import * as Types from './types.ts'

const TIMEOUT_MS = 8000;

export async function fetchWeather(coord: Types.Coord): Promise<Types.OpenWeatherAPIResponse> {
  const url = 
    "https://api.openweathermap.org/data/2.5/weather" +
    `?lat=${coord.lat}&lon=${coord.lon}&appid=${Config.token}` +
    "&units=metric";

  const controller = new AbortController();
  const timeoutID = setTimeout(() => controller.abort(), TIMEOUT_MS);
  
  let res;
  try {
    res = await fetch(url, { signal: controller.signal });
    clearTimeout(timeoutID);
  } catch (e) {
    console.log(e);
    return { ok: false }
  }

  const data = await res.json();
  return Types.ConvertToOpenWeaterAPIResponse(data);
}
