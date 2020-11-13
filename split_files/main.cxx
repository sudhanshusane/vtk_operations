#include <vtkRectilinearGrid.h>
#include <vtkRectilinearGridReader.h>
#include <vtkSmartPointer.h>
#include <vtkPointData.h>
#include <vtkDataArray.h>
#include <iostream>
#include <sstream>


int main(int argc, char *argv[])
{
	vtkSmartPointer<vtkRectilinearGridReader> reader = vtkSmartPointer<vtkRectilinearGridReader>::New();
	reader->SetFileName(argv[1]);
	reader->Update();

	vtkSmartPointer<vtkRectilinearGrid> rgrid = vtkSmartPointer<vtkRectilinearGrid>::New();

	int dims[3];
	rgrid->GetDimensions(dims);	

	float *X = (float*) rgrid->GetXCoordinates()->GetVoidPointer(0);
	float *Y = (float*) rgrid->GetXCoordinates()->GetVoidPointer(0);

	float *xvel = (float*) rgrid->GetPointData()->GetScalars("u");
	float *yvel = (float*) rgrid->GetPointData()->GetScalars("v");

	std::cout << xvel[0] << " " << yvel[0] << std::endl;

	// Get dimensions
	// Get X, Y, Z coordinates
	// Get individual fields
	
	// Loop over Z dims
	// Create 2D slice data set and write it out. 
}
