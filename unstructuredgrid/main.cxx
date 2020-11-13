#include <iostream>
#include <vtkSmartPointer.h>
#include <vtkUnstructuredGridReader.h>
#include <vtkUnstructuredGrid.h>
#include <vtkPointSet.h>
#include <vtkIdList.h>

int main(int argc, char *argv[])
{
	std::cout << "Extracting data from an unstructured vtk file." << std::endl;

	auto reader = vtkSmartPointer<vtkUnstructuredGridReader>::New();
	reader->SetFileName(argv[1]);
	reader->Update();
	vtkSmartPointer<vtkUnstructuredGrid> ugrid = reader->GetOutput();
	int num_cells = ugrid->GetNumberOfCells();
	std::cout << "Number of cells: " <<	num_cells << std::endl;

	int num_points = ugrid->GetNumberOfPoints();
	std::cout << "Number of points: " <<	num_points << std::endl;
	
	float *pts = (float*)malloc(sizeof(float)*3*num_points);
	// This array will store all the vertex locations in the format x0 y0 z0 x1 y1 z1 x2 y2 z2 .. xn yn zn
	
	for(int i = 0; i < num_points; i++)
	{
		double p[3];
		ugrid->GetPoint(i, p);
		pts[i*3+0] = p[0];
		pts[i*3+1] = p[1];
		pts[i*3+2] = p[2];
	}
	
	std::cout << "First point : " << pts[0] << " " << pts[1] << " " << pts[2] << std::endl; 
	std::cout << "Last point : " << pts[num_points*3-3] << " " << pts[num_points*3-2] << " " << pts[num_points*3-1] << std::endl; 

	for(int i = 0; i < 5; i++)
	{
		vtkIdList *ids;
		ugrid->GetCellPoints(i, ids);
		std::cout << "Cell " << i << " consists of indices: " << ids[0] << ", " << ids[1] << ", " << ids[2] << ", " << ids[3] << ", " << ids[4] << ", " << ids[5] << ", " << ids[6] << ", " << ids[7] << std::endl;
	}		
}
