import java.io.IOException;
import java.util.StringTokenizer;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.util.GenericOptionsParser;

public class WebAccessLog {

    public static class Map extends Mapper<Object, Text, Text, LongWritable> {
        // Mapper<Input Key, Input Value, Output Key, Output Value>
        private final static LongWritable one = new LongWritable(1);
        private Text ip = new Text(); // IP address
        private Text date = new Text(); // date (string)
        private Text time = new Text(); // time (hour only, string)
        private Text method = new Text(); // HTTP request method (GET/POST/etc)
        private Text path = new Text(); // URL path
        private Text http_code = new Text(); // HTTP code (200/etc)
        private LongWritable size = new LongWritable(0); // Request/Response size (in Bytes)

        @Override
        public void map(Object key, Text value, Context context) throws IOException, InterruptedException {
            StringTokenizer itr = new StringTokenizer(value.toString());
            if (itr.countTokens() != 7) return;
            if (itr.hasMoreTokens()) ip.set(itr.nextToken()); // IP address
            if (itr.hasMoreTokens()) date.set(itr.nextToken()); // date (string)
            if (itr.hasMoreTokens()) time.set(itr.nextToken().substring(0, 2)); // time (hour only, string)
            if (itr.hasMoreTokens()) method.set(itr.nextToken()); // HTTP request method (GET/POST/etc)
            if (itr.hasMoreTokens()) path.set(itr.nextToken()); // URL path
            if (itr.hasMoreTokens()) http_code.set(itr.nextToken()); // HTTP code (200/etc)
            if (itr.hasMoreTokens()) size = new LongWritable(Long.parseLong(itr.nextToken())); // Request/Response size (in Bytes)
            context.write(time, one); // count request amount according to time
            // context.write(time, size); // count data size according to time
        }
    }

    public static class Reduce extends Reducer<Text, LongWritable, Text, LongWritable> {
        // Reducer<Input Key, Input Value, Output Key, Output Value>
        private LongWritable result = new LongWritable(0);
        @Override
        public void reduce(Text key, Iterable<LongWritable> values, Context context) throws IOException, InterruptedException {
            // sum up the values
            long sum = 0;
            for (LongWritable val : values) {
                sum += val.get();
            }
            result.set(sum);
            context.write(key, result);
        }
    }

    public static void main(String[] args) throws Exception {
        Configuration conf = new Configuration();
        String[] otherArgs = new GenericOptionsParser(conf, args).getRemainingArgs(); // Input folder & Output folder
        if (otherArgs.length != 2) {
            System.err.println("Usage: WebAccessLog <in> <out>");
            System.exit(2);
        }
        Job job = Job.getInstance(conf, "WebAccessLog");
        job.setJarByClass(WebAccessLog.class);
        job.setMapperClass(Map.class);
        job.setReducerClass(Reduce.class);
        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(LongWritable.class);
        FileInputFormat.addInputPath(job, new Path(otherArgs[0]));
        FileOutputFormat.setOutputPath(job, new Path(otherArgs[1]));
        System.exit(job.waitForCompletion(true) ? 0 : 1);
    }

}
