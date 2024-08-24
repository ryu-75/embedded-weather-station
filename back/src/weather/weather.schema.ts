import { EntitySchema } from 'typeorm';
import { Weather } from './weather.entity';

export const WeatherSchema = new EntitySchema<Weather>({
  name: 'Weather',
  target: Weather,
  columns: {
    id: {
      type: Number,
      primary: true,
      generated: true,
    },
    temperature: {
      type: String,
    },
    pressure: {
      type: String,
    },
    timestamp: {
      type: Date,
      default: () => new Date(),
    },
  },
});
