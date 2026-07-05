export interface Coord {
  lat: number,
  lon: number,
}

export interface Weather {
  id: number,
  main: string,
  description: string,
  icon: string,
}

export interface WeatherMain {
  temp: number,
  feels: number,
  tempMin: number,
  tempMax: number,
  pressure: number,
  humidity: number,
}

export interface WeatherWind {
  speed: number,
  deg: number,
  gust: number,
}

export interface OpenWeatherAPIResponse {
  weather?: Weather[],
  main?: WeatherMain,
  wind?: WeatherWind,
  rain?: Record<string, number>,
  name?: string, // City Name
  ok: boolean,
}

export function ConvertToOpenWeaterAPIResponse(res: any): OpenWeatherAPIResponse {
  let result: OpenWeatherAPIResponse = {
    weather: res.weather.map((w: any): Weather => ({
      id: w.id,
      main: w.main,
      description: w.description,
      icon: w.icon,
    })),

    main: {
      temp: res.main.temp,
      feels: res.main.feels_like,
      tempMin: res.main.temp_min,
      tempMax: res.main.temp_max,
      pressure: res.main.pressure,
      humidity: res.main.humidity,
    },
  
    wind: {
      speed: res.wind.speed,
      deg: res.wind.deg,
      gust: res.wind.gust,
    },

    rain: res.rain,
    name: res.name,
    ok: res.cod >= 200 && res.cod <= 299,
  }

  return result;
}
